#pragma once

#include <vector>
#include "card.hpp"

class Hand {
	private:
		std::vector<Card> cards;
		int score = 0;
		int visibleScore = 0;

		void recomputeScore();
	public:
		void add(const Card& card, bool visibility);
		
		int getScore() { return this->score; }
		int getVisibleScore() { return this->visibleScore; }
		Card& getCurrentCard() { return this->cards.back(); }

		bool isBusted();
		bool isBlackjack();

		void display();
};

void printCardsRow(const std::vector<std::vector<std::string>>& sprites);
