#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include "card.hpp"

class Deck {
	private:
		std::vector<Card> cards;
		std::mt19937 rng;
	public:
		Deck();

		void init();
		void clear();
		void shuffle();
		Card draw();
};
