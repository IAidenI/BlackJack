#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <limits>
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

		void clearScreen();
		void display();
		void checkImediate();
	public:
		Game();

		GameStatus getStatus() const { return this->gameStatus; }
		
		void start();
};
