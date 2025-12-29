#include "game.hpp"
#include "deck.hpp"
#include "hand.hpp"

int main() {
	Game game;

	switch (game.getStatus()) {
		case GameStatus::PLAYER_WIN: {
			std::cout << "Vous avez gagné." << std::endl;
			break;
		}
		case GameStatus::DEALER_WIN: {
			std::cout << "Vous avez perdu." << std::endl;
			break;
		}
		case GameStatus::PUSH: {
			std::cout << "Vous avez fais égalité." << std::endl;
			break;
		}
		case GameStatus::PLAYER_TURN: {
			std::cout << "La game est en cours..." << std::endl;
			break;
		}
		default: {
			std::cout << "Error" << std::endl;
			break;
		}
	}
	return 0;
}
