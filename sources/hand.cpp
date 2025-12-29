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

static void printCardsRow(const std::vector<std::vector<std::string>>& sprites) {
    if (sprites.empty()) return;
    const size_t H = sprites[0].size();

    for (size_t y = 0; y < H; ++y) {
        for (size_t i = 0; i < sprites.size(); ++i) {
            std::cout << sprites[i][y];
            if (i + 1 < sprites.size()) std::cout << "  ";
        }
        std::cout << "\n";
    }
}

void Hand::display() {
	this->recomputeScore();

	std::cout << " Score : " << this->visibleScore << "\n\n";

    std::vector<std::vector<std::string>> sprites;
    sprites.reserve(this->cards.size());
    for (const Card& card : this->cards) {
        sprites.push_back(card.render());
    }
    printCardsRow(sprites);
}
