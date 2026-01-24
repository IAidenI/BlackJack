#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <limits>
#include "deck.hpp"
#include "hand.hpp"
#include "utils.hpp"

#define VISIBLE true
#define HIDDEN false

enum class GameStatus {
	INIT,
	PLAYER_TURN,
	DEALER_TURN,
	DEALER_REVEAL,
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

		void checkImediate();
	public:
		Game();

		void clear();
		void newRound();

		void playerHit();
		void playerStand();

		void dealerStep();

		bool isRoundOver();
		GameStatus getStatus() const { return this->gameStatus; }

		Hand& getPlayerHand() { return this->playerHand; }
		Hand& getDealerHand() { return this->dealerHand; }
};
