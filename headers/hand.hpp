#pragma once

#include <vector>
#include "card.hpp"

class Hand {
	private:
		std::vector<Card> cards;
		int score = 0;
	public:
		void add(const Card& card);
		int getScore() { return this->score; }

		bool isBusted();
		bool isBlackjack();
};
