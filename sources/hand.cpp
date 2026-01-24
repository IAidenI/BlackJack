#include "hand.hpp"

void Hand::add(const Card& card, bool visibility) {
	this->cards.push_back(card);
	this->cards.back().setVisibility(visibility);

    this->recomputeScore();
};

void Hand::clear() {
    this->cards.clear();
    this->score = 0;
    this->visibleScore = 0;
}

bool Hand::isBusted() {
	return this->score > 21;
}

bool Hand::isBlackjack() {
	return this->score == 21;
}

void Hand::recomputeScore() {
    int total = 0;
    int visibleTotal = 0;

    int aces = 0;
    int visibleAces = 0;

    for (const Card& card : cards) {
        int value = card.getValue();
        total += value;

        if (card.getName() == "As") aces++;

        if (card.getVisibility()) {
            visibleTotal += value;
            if (card.getName() == "As") visibleAces++;
        }
    }

    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }

    while (visibleTotal > 21 && visibleAces > 0) {
        visibleTotal -= 10;
        visibleAces--;
    }

    this->score = total;
    this->visibleScore = visibleTotal;
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

void printCardsRow(const std::vector<std::vector<std::string>>& sprites) {
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
