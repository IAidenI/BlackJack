#pragma once

#include <string>

enum class LoanType {
    SMALL,
    MEDIUM,
    LARGE
};

struct LoanOffer {
    LoanType type;
    int amount;
    float interestRate;
    int minTokensRequired;
};

struct ActiveLoan {
    LoanType type;
    int remaining;
    bool active;
};

inline std::string loanTypeToString(LoanType t) {
    switch (t) {
        case LoanType::SMALL: return "SMALL";
        case LoanType::MEDIUM: return "MEDIUM";
        case LoanType::LARGE: return "LARGE";
    }
    return "SMALL";
}

inline LoanType loanTypeFromString(const std::string& s) {
    if (s == "SMALL")  return LoanType::SMALL;
    if (s == "MEDIUM") return LoanType::MEDIUM;
    if (s == "LARGE")  return LoanType::LARGE;
    return LoanType::SMALL;
}
