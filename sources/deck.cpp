#include "deck.hpp"

Deck::Deck() : rng(std::random_device{}()) {
	this->init();
	this->shuffle();
}

void Deck::init() {
	this->cards.clear();

    for (const auto& [name, value]: Card::ranks) {
        for (const auto& familly: Card::famillies) {
            this->cards.emplace_back(name, familly, value);
        }
    }
}

void Deck::clear() {
    this->cards.clear();
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
