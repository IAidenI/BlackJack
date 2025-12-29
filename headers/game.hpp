#pragma once

#include <chrono>
#include <thread>
#include "deck.hpp"
#include "hand.hpp"

#define VISIBLE true
#define HIDDEN false

enum class GameStatus {
	INIT,
	PLAYER_TURN,
	DEALER_TURN,
	PLAYER_WIN,
	DEALER_WIN,
	PUSH
};

enum class PlayerStatus {
	PLAYING,
	STAND,
	BUSTED,
	BLACKJACK
};

class Game {
	private:
		Hand playerHand;
		Hand dealerHand;
		Deck deck;

		GameStatus gameStatus = GameStatus::INIT;
		PlayerStatus playerStatus = PlayerStatus::PLAYING;
	public:
		Game();

		GameStatus getStatus() const { return this->gameStatus; }
		void checkImediate();
		void display();
		void clearScreen();
		void start();
};
