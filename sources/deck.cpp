#include "deck.hpp"

Deck::Deck() : rng(std::random_device{}()) {
	this->init();
	this->shuffle();
}

void Deck::init() {
	this->cards.clear();

	std::vector<std::string> cardNames = {
        "As", "Deux", "Trois", "Quatre", "Cinq",
        "Six", "Sept", "Huit", "Neuf", "Dix",
        "Valet", "Dame", "Roi"
    };

    std::vector<std::string> cardFamillies = {
        "Coeur", "Trèfle", "Carreau", "Pique"
    };

    for (std::string familly: cardFamillies) {
        int value = 1;
        for (std::string name: cardNames) {
            this->cards.push_back(Card(name, familly, value++));
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
