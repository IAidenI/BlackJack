#include "game.hpp"

Game::Game() : deck() {}

void Game::init() {
	this->playerHand.add(this->deck.draw(), VISIBLE);
	this->playerHand.add(this->deck.draw(), VISIBLE);

	this->dealerHand.add(this->deck.draw(), VISIBLE);
	this->dealerHand.add(this->deck.draw(), HIDDEN);

	this->checkImediate();
}

void Game::checkImediate() {
	bool pBJ = this->playerHand.isBlackjack();
	bool dBJ = this->dealerHand.isBlackjack();

	if (pBJ && dBJ) this->gameStatus = GameStatus::PUSH;
	else if (pBJ) this->gameStatus = GameStatus::PLAYER_WIN_WITH_BJ;
	else if (dBJ) this->gameStatus = GameStatus::DEALER_WIN;
}

void Game::display() {
	std::cout << "=== Main du croupier ===" << std::endl;
	this->dealerHand.display();
	std::cout << std::endl;

	std::cout << "=== Votre main ===" << std::endl;
	this->playerHand.display();
}

void Game::clearScreen() {
	std::cout << "\033[2J\033[H";
}

void Game::start() {
	while (true) {
		this->clearScreen();

		switch(this->gameStatus) {
			case GameStatus::INIT: {
				std::cout << "Le jeu commence !" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				this->gameStatus = GameStatus::PLAYER_TURN;
				this->init();
				break;
			}
			case GameStatus::PLAYER_TURN: {
				this->display();

				while (this->playerStatus == PlayerStatus::PLAYING) {
					std::cout << "Voulez-vous tirer une carte ? (y/n) : ";
					char choice;
					std::cin >> choice;
					choice = (char)std::tolower((unsigned char)choice);

					if (choice == 'y') {
						this->playerHand.add(this->deck.draw(), VISIBLE);
						this->clearScreen();
						this->display();

						if (this->playerHand.isBusted()) {
							this->playerStatus = PlayerStatus::BUSTED;
							this->gameStatus = GameStatus::DEALER_WIN;
						} else if (this->playerHand.isBlackjack()) {
							this->playerStatus = PlayerStatus::BLACKJACK;
							this->gameStatus = GameStatus::PLAYER_WIN_WITH_BJ;
						}
					} else if (choice == 'n') {
						this->playerStatus = PlayerStatus::STAND;
						this->gameStatus = GameStatus::DEALER_TURN;
					} else {
						this->clearScreen();
						this->display();
						std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
					}
				}
				break;
			}
			case GameStatus::DEALER_TURN: {
				this->display();

				this->dealerHand.getCurrentCard().setVisibility(VISIBLE);
				this->clearScreen();
				this->display();
				std::this_thread::sleep_for(std::chrono::milliseconds(1300));

				while (this->dealerHand.getScore() < 17) {
					this->dealerHand.add(this->deck.draw(), VISIBLE);
					this->clearScreen();
					this->display();
					std::this_thread::sleep_for(std::chrono::milliseconds(1300));
				}

				if (this->dealerHand.isBusted()) {
					this->gameStatus = GameStatus::PLAYER_WIN;
				} else if (this->dealerHand.getScore() > this->playerHand.getScore()) {
					this->gameStatus = GameStatus::DEALER_WIN;
				} else if (this->dealerHand.getScore() < this->playerHand.getScore()) {
					this->gameStatus = GameStatus::PLAYER_WIN;
				} else {
					this->gameStatus = GameStatus::PUSH;
				}
				break;
			}
			case GameStatus::PLAYER_WIN:
			case GameStatus::DEALER_WIN:
			case GameStatus::PUSH: {
				this->clearScreen();
				this->display();
				return;
			}
			default:
				return;
		}
	}
}

void Game::clear() {
	this->playerHand.clear();
	this->dealerHand.clear();
	
	this->gameStatus = GameStatus::INIT;
	this->playerStatus = PlayerStatus::PLAYING;

	this->deck.clear();
	this->deck.init();
	this->deck.shuffle();
}
