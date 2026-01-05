#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "bcrypt.h"

#define PATTERN_USERNAME "username:"
#define PATTERN_PASSWORD "password:"
#define PATTERN_TOKENS   "tokens:"
#define DEFAULT_TOKENS   1000

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
        bool logged = false;

        std::string accountDir = "accounts";
        
        bool loadAccountFile(std::string path, std::string& username, std::string& hash, int& tokens);
        void encrpyt(std::string path);
    public:
        Account();

        std::string getUsername() { return this->username; }
        int getTokens() { return this->tokens; }
        bool isConnected() { return this->logged; }

        void changeUsername(std::string newUsername) { this->username = newUsername; }
        void changePassword(std::string newPassword) { this->hashPassword = bcrypt::generateHash(newPassword); }
        bool isPasswordCorrect(std::string password) { return bcrypt::validatePassword(password, this->hashPassword); };

        AccountStatus create(std::string username, std::string password);
        AccountStatus remove();
        AccountStatus login(std::string username, std::string password);
        void logout();

        bool canBet(int amount);
        void applyResult(int bet, Result result);
        AccountStatus save();
};