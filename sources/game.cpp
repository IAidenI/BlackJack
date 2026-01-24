#include "game.hpp"

Game::Game() : deck() {}

void Game::clear() {
	this->playerHand.clear();
	this->dealerHand.clear();
	
	this->gameStatus = GameStatus::INIT;
	this->playerStatus = PlayerStatus::PLAYING;

	this->deck.clear();
	this->deck.init();
	this->deck.shuffle();
}

void Game::newRound() {
	this->clear();

	this->playerHand.add(this->deck.draw(), VISIBLE);
	this->playerHand.add(this->deck.draw(), VISIBLE);

	this->dealerHand.add(this->deck.draw(), VISIBLE);
	this->dealerHand.add(this->deck.draw(), HIDDEN);

	this->checkImediate();
}

void Game::checkImediate() {
	bool pBJ = this->playerHand.isBlackjack();
	bool dBJ = this->dealerHand.isBlackjack();
	bool gameOver = this->playerHand.isBusted();

	if (pBJ && dBJ) this->gameStatus = GameStatus::PUSH;
	else if (pBJ) this->gameStatus = GameStatus::PLAYER_WIN_WITH_BJ;
	else if (dBJ || gameOver) this->gameStatus = GameStatus::DEALER_WIN;
	else this->gameStatus = GameStatus::PLAYER_TURN;
}

void Game::playerHit() {
	if (this->gameStatus != GameStatus::PLAYER_TURN) return ;

	this->playerHand.add(this->deck.draw(), VISIBLE);

	if (this->playerHand.isBusted()) {
		this->playerStatus = PlayerStatus::BUSTED;
		this->gameStatus = GameStatus::DEALER_WIN;
	}

	if (this->playerHand.isBlackjack()) {
		this->playerStatus = PlayerStatus::BLACKJACK;
		this->gameStatus = GameStatus::PLAYER_WIN_WITH_BJ;
	}
}

void Game::playerStand() {
	if (this->gameStatus != GameStatus::PLAYER_TURN) return;

	this->playerStatus = PlayerStatus::STAND;
	this->gameStatus = GameStatus::DEALER_REVEAL;
}

void Game::dealerStep() {
    if (gameStatus == GameStatus::DEALER_REVEAL) {
        dealerHand.getCurrentCard().setVisibility(VISIBLE);
        gameStatus = GameStatus::DEALER_TURN;
        return;
    }

	if (this->gameStatus != GameStatus::DEALER_TURN) return;

	if (this->dealerHand.getScore() >= 17) {
		if (this->dealerHand.getScore() > this->playerHand.getScore()) this->gameStatus = GameStatus::DEALER_WIN;
		else if (this->dealerHand.getScore() < this->playerHand.getScore()) this->gameStatus = GameStatus::PLAYER_WIN;
		else this->gameStatus = GameStatus::PUSH;
	} else {
		this->dealerHand.add(this->deck.draw(), VISIBLE);
		if (this->dealerHand.isBusted()) this->gameStatus = GameStatus::PLAYER_WIN;
	}
}

bool Game::isRoundOver() {
	return this->gameStatus == GameStatus::PLAYER_WIN ||
		   this->gameStatus == GameStatus::PLAYER_WIN_WITH_BJ ||
		   this->gameStatus == GameStatus::DEALER_WIN ||
		   this->gameStatus == GameStatus::PUSH;
}
