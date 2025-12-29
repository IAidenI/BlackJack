#include "game.hpp"
#include "deck.hpp"
#include "hand.hpp"

int main() {
	Game game;

	game.start();

	switch (game.getStatus()) {
		case GameStatus::PLAYER_WIN: {
			std::cout << "Vous avez gagné !" << std::endl;
			break;
		}
		case GameStatus::DEALER_WIN: {
			std::cout << "Le croupier a gagné !" << std::endl;
			break;
		}
		case GameStatus::PUSH: {
			std::cout << "Égalité !" << std::endl;
			break;
		}
		default: {
			std::cout << "Le jeu s'est terminé de manière inattendue." << std::endl;
			break;
		}
	}
	return 0;
}
