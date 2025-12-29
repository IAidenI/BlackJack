#pragma once

#include <vector>
#include "card.hpp"

class Hand {
	private:
		std::vector<Card> cards;
		int score = 0;
		int visibleScore = 0;
	public:
		void add(const Card& card, bool visibility);
		int getScore() { return this->score; }
		int getVisibleScore() { return this->visibleScore; }

		bool isBusted();
		bool isBlackjack();

		Card& getCurrentCard();
		void recomputeScore();
		void display();
};
