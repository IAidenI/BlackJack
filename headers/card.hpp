#pragma once

#include <iostream>
#include <string>

class Card {
	private:
		std::string name;
		std::string familly;
		int value;
		bool visibility = false;
	public:
		Card(std::string name, std::string familly, int value);
		Card() { this->name = "Inconnue"; this->familly = "Inconnue"; this->value = -1; this->visibility = false; }

		//std::string getName() { return this->name; }
		//std::string getFamilly() { this->familly; }
		int getValue() const { return this->value; }
		bool getVisibility() const { return this->visibility; }

		void setVisibility(bool visibility) { this->visibility = visibility; }

		void display();
};
