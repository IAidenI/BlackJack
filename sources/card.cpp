#include "card.hpp"

Card::Card(std::string name, std::string familly, int value) {
	this->name = name;
	this->familly = familly;
	this->value = value;
}

void Card::display() {
	if (!this->visibility) {
		std::cout << "[ Card ] Carte cachée." << std::endl;
		return;
	}

	std::cout << "[ Card ] Nom     : " << this->name << std::endl;
	std::cout << "         Famille : " << this->familly << std::endl;
	std::cout << "         Valeur  : " << this->value << std::endl;
}
