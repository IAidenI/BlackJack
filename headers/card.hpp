#pragma once

#include <vector>
#include <iostream>
#include <string>

class Card {
	private:
		std::string name;
		std::string familly;
		int value;
		bool visibility = false;

		std::string rankStr() const;
		std::string suitChar() const;
	public:
		Card(std::string name, std::string familly, int value);
		Card() { this->name = "Inconnue"; this->familly = "Inconnue"; this->value = -1; this->visibility = false; }

		int getValue() const { return this->value; }
		bool getVisibility() const { return this->visibility; }

		void setVisibility(bool visibility) { this->visibility = visibility; }

		void display();

    	std::vector<std::string> render() const;
    	std::vector<std::string> renderHidden() const;
};
