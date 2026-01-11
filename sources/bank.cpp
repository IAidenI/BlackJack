#include "bank.hpp"

Bank::Bank() {
    this->loanOffers.push_back({LoanType::SMALL,  10,   0.30f, 0});
    this->loanOffers.push_back({LoanType::MEDIUM, 500,  0.20f, 50});
    this->loanOffers.push_back({LoanType::LARGE,  1000, 0.15f, 500});
}

bool Bank::requestLoan(Account& user, LoanType type) {
    if (user.hasActiveLoan()) return false;

    for (auto& offer: this->loanOffers) {
        if (offer.type == type) {
            if (user.getTokens() <= offer.minTokensRequired) return false;

            user.addTokens(offer.amount);
            auto& loan = user.getLoan();
            loan.type = type;
            loan.remaining = static_cast<int>(offer.amount * (1.0f + offer.interestRate));
            loan.active = true;
            return true;
        }
    }
    return false;
}

bool Bank::repay(Account& user, int& amount) {
    auto& loan = user.getLoan();
    if (!loan.active || amount <= 0) return false;

    int pay = std::min(amount, loan.remaining);
    loan.remaining -= pay;
    amount -= pay;

    if (loan.remaining <= 0) {
        loan.active = false;
        loan.remaining = 0;
    }
    return pay > 0;
}
