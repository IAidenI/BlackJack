#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "bcrypt.h"
#include "loan.hpp"

#define PATTERN_USERNAME       "username:"
#define PATTERN_PASSWORD       "password:"
#define PATTERN_TOKENS         "tokens:"
#define PATTERN_LOAN_ACTIVE    "loan_a:"
#define PATTERN_LOAN_TYPE      "loan_t:"
#define PATTERN_LOAN_REMAINING "loan_r:"
#define DEFAULT_TOKENS   100

enum class AccountStatus {
    CREATED,
    REMOVED,
    EXISTS,
    NOT_EXISTS,
    LOGGED,
    NOT_LOGGED,
    SAVED,
    ERROR
};

enum class Result {
    WIN,
    BLACKJACK,
    LOSE,
    PUSH
};

class Account {
    private:
        std::string username = "";
        std::string fileUsername = "";
        std::string hashPassword = "";
        int tokens = 0;
        ActiveLoan loan;
        bool logged = false;

        std::string accountDir = "accounts";
        
        bool loadAccountFile(std::string path, std::string& username, std::string& hash, int& tokens, ActiveLoan& loan);
        void encrpyt(std::string path);
    public:
        Account();

        std::string getUsername() { return this->username; }
        int getTokens() { return this->tokens; }
        ActiveLoan& getLoan() { return this->loan; }
        bool hasActiveLoan() { return this->loan.active; }
        bool isConnected() { return this->logged; }

        void changeUsername(std::string newUsername) { this->username = newUsername; }
        void changePassword(std::string newPassword) { this->hashPassword = bcrypt::generateHash(newPassword); }
        bool isPasswordCorrect(std::string password) { return bcrypt::validatePassword(password, this->hashPassword); };
        void addTokens(int amount) { this->tokens += amount; }

        AccountStatus create(std::string username, std::string password);
        AccountStatus remove();
        AccountStatus login(std::string username, std::string password);
        void logout();

        bool canBet(int amount);
        AccountStatus save();
};