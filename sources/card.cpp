#include "card.hpp"

static std::string padRight(const std::string& s, size_t w) {
    if (s.size() >= w) return s;
    return s + std::string(w - s.size(), ' ');
}

static std::string centerText(const std::string& t, size_t w) {
    if (t.size() >= w) return t.substr(0, w);
    size_t left = (w - t.size()) / 2;
    size_t right = w - t.size() - left;
    return std::string(left, ' ') + t + std::string(right, ' ');
}

Card::Card(std::string name, std::string familly, int value) {
	this->name = name;
	this->familly = familly;
	this->value = value;
}


std::string Card::rankStr() const {
    if (name == "As") return "A";
    if (name == "Valet") return "J";
    if (name == "Dame") return "Q";
    if (name == "Roi") return "K";
    if (name == "Dix") return "10";
    if (name == "Neuf") return "9";
    if (name == "Huit") return "8";
    if (name == "Sept") return "7";
    if (name == "Six") return "6";
    if (name == "Cinq") return "5";
    if (name == "Quatre") return "4";
    if (name == "Trois") return "3";
    if (name == "Deux") return "2";
    return "?";
}

std::string Card::suitChar() const {
    if (familly == "Pique") return "♠";
    if (familly == "Coeur") return "♥";
    if (familly == "Carreau") return "♦";
    if (familly == "Trèfle") return "♣";
    return "?";
}

void Card::display() {
	if (!this->visibility) {
		const auto lines = this->renderHidden();
		for (const std::string& line : lines) {
			std::cout << line << '\n';
		}
	} else {
		std::cout << "[ Card ] Nom     : " << this->name << std::endl;
		std::cout << "         Famille : " << this->familly << std::endl;
		std::cout << "         Valeur  : " << this->value << std::endl << std::endl;

		const auto lines = this->render();
		for (const std::string& line : lines) {
			std::cout << line << '\n';
		}
	}
}

std::vector<std::string> Card::renderHidden() const {
	const std::string label = centerText("Cachée", 13);
    return {
        "╭───────────╮",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "│░░░░░░░░░░░│",
        "╰───────────╯",
		label
    };
}

std::vector<std::string> Card::render() const {
    if (!visibility) return this->renderHidden();

    const std::string r = this->rankStr();
    const std::string s = this->suitChar();

    std::string top = "│" + padRight(r, 11) + "│";
    std::string bot = "│" + padRight("", 11 - r.size()) + r + "│";

	const std::string label = centerText(this->name, 13);

    return {
        "╭───────────╮",
        top,
        "│           │",
        "│     " + s + "     │",
        "│           │",
        "│     " + s + "     │",
        "│           │",
        bot,
        "╰───────────╯",
		label,
    };
}
