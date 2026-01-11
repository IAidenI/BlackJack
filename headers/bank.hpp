#pragma once

#include <vector>
#include "loan.hpp"
#include "account.hpp"

class Bank {
    private:
        std::vector<LoanOffer> loanOffers;

    public:
        Bank();

        std::vector<LoanOffer> getLoanOffers() { return this->loanOffers; }
        bool requestLoan(Account& user, LoanType type);
        bool repay(Account& user, int& amount);
};
