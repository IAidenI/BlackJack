#pragma once

#include "deck.hpp"
#include "hand.hpp"

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
		GameStatus checkImediate();
};
