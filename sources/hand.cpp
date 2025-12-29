#include "hand.hpp"

void Hand::add(const Card& card) {
	this->cards.push_back(card);
	this->score += card.getValue();
};

bool Hand::isBusted() {
	return this->score > 21;
}

bool Hand::isBlackjack() {
	return this->score == 21;
}
