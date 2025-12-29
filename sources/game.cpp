#include "game.hpp"

 Game::Game() : deck() {
	this->playerHand.add(this->deck.draw());
	this->playerHand.add(this->deck.draw());

	this->dealerHand.add(this->deck.draw());
	this->dealerHand.add(this->deck.draw());

	this->status = this->checkImediate();
}

Status Game::checkImedtiate() {
	bool pBJ = this->playerHand.isBlackjack();
	bool dBJ = this->dealerHand.isBlackjack();

	if (pBJ && dBJ) return GameStatus::PUSH;
	if (pBJ) return GameStatus::PLAYER_WIN;
	if (dBJ) return GameStatus::DEALER_WIN;

	return GameStatus::PLAYER_TURN;
}

