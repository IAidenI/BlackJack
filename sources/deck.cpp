#include "deck.hpp"

Deck::Deck() : rng(std::random_device{}()) {
	this->init();
	this->shuffle();
}

void Deck::init() {
	this->cards.clear();

    std::vector<Rank> ranks = {
        {"As", 11}, {"Deux", 2}, {"Trois", 3}, {"Quatre", 4},
        {"Cinq", 5}, {"Six", 6}, {"Sept", 7}, {"Huit", 8},
        {"Neuf", 9}, {"Dix", 10}, {"Valet", 10}, {"Dame", 10},
        {"Roi", 10}
    };

    std::vector<std::string> cardFamillies = {
        "Coeur", "Trèfle", "Carreau", "Pique"
    };

    for (std::string familly: cardFamillies) {
        for (Rank rank: ranks) {
            this->cards.emplace_back(rank.name, familly, rank.value);
        }
    }
}

void Deck::shuffle() {
	std::shuffle(this->cards.begin(), this->cards.end(), this->rng);
}

Card Deck::draw() {
	if (this->cards.size() <= 0) return Card();
	Card card = this->cards.front();
	this->cards.erase(this->cards.begin());
	return card;
}

void Deck::debug() {
	std::cout << "[ DEBUG ] first card :" << std::endl;
	this->cards.front().display();
	std::cout << std::endl;
}
