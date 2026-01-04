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
	PLAYER_WIN_WITH_BJ,
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

		void display();
		void checkImediate();
	public:
		Game();
		void init();

		GameStatus getStatus() const { return this->gameStatus; }
		
		void clearScreen();
		void start();
		void clear();
};
