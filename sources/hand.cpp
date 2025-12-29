#include "hand.hpp"

void Hand::add(const Card& card, bool visibility) {
	this->cards.push_back(card);
	this->cards.back().setVisibility(visibility);
	this->score += card.getValue();
	if (visibility) this->visibleScore += card.getValue();
};

bool Hand::isBusted() {
	return this->score > 21;
}

bool Hand::isBlackjack() {
	return this->score == 21;
}

Card& Hand::getCurrentCard() {
	return this->cards.back();
}

void Hand::recomputeScore() {
    this->score = 0;
    this->visibleScore = 0;

    for (const Card& card : cards) {
        this->score += card.getValue();
        if (card.getVisibility()) this->visibleScore += card.getValue();
    }
}

void Hand::display() {
	this->recomputeScore();
	
	std::cout << "[ Hand ] Score : " << this->visibleScore << std::endl;
	for (Card card: this->cards) {
		card.display();
	}
}
