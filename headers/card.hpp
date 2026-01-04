#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

class Card {
	private:
		std::string name;
		std::string familly;
		int value;
		bool visibility = false;

		std::string rankStr() const;
		std::string suitChar() const;
	public:
		Card();
		Card(std::string name, std::string familly, int value);

		std::string getName() const { return this->name; }
		std::string getFamilly() const { return this->familly; }
		int getValue() const { return this->value; }
		bool getVisibility() const { return this->visibility; }

		void setVisibility(bool visibility) { this->visibility = visibility; }
		void setValue(bool value) { this->value = value; }

		void display();
    	std::vector<std::string> render() const;
    	std::vector<std::string> renderHidden() const;

		bool operator==(const Card &other) const;

		static bool isValid(std::string name, std::string familly);
		static Card create(std::string name, std::string familly);

		static std::unordered_map<std::string, int> ranks;
    	static std::vector<std::string> famillies;
};

std::string padRight(const std::string& s, size_t w);
std::string centerText(const std::string& t, size_t w);
