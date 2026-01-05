#include "account.hpp"

Account::Account() {
    std::filesystem::create_directory(this->accountDir);
}

AccountStatus Account::create(std::string username, std::string password) {    
    std::string filePath = this->accountDir + "/" + username + ".acc";

    if (std::filesystem::exists(filePath)) return AccountStatus::EXISTS;
    
    std::ofstream file(filePath);
    if (!file) return AccountStatus::ERROR;

    std::string hash = bcrypt::generateHash(password);
    file << PATTERN_USERNAME << username << "\n";
    file << PATTERN_PASSWORD << hash << "\n";
    file << PATTERN_TOKENS  << std::to_string(DEFAULT_TOKENS) << "\n";
    file.close();

    return AccountStatus::CREATED;
}

AccountStatus Account::remove() {
    if (!this->logged) return AccountStatus::NOT_LOGGED;
    std::string filePath = this->accountDir + "/" + this->username + ".acc";
    if (std::filesystem::remove(filePath)) {
        this->logout();
        return AccountStatus::REMOVED;
    }
    else return AccountStatus::NOT_EXISTS;
}

bool Account::loadAccountFile(std::string path, std::string& username, std::string& hash, int& balance) {
    std::ifstream file(path);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind(PATTERN_USERNAME, 0) == 0) username = line.substr(std::string(PATTERN_USERNAME).size());
        else if (line.rfind(PATTERN_PASSWORD, 0) == 0) hash = line.substr(std::string(PATTERN_PASSWORD).size());
        else if (line.rfind(PATTERN_TOKENS, 0) == 0) balance = std::stoi(line.substr(std::string(PATTERN_TOKENS).size()));
    }
    return !username.empty() && !hash.empty() && balance != 0;
}

AccountStatus Account::login(std::string username, std::string password) {
    std::string filePath = this->accountDir + "/" + username + ".acc";

    if (!std::filesystem::exists(filePath)) return AccountStatus::NOT_EXISTS;

    std::string usernameFound = "";
    std::string hashFound = "";
    int balanceFound = 0;
    if (!this->loadAccountFile(filePath, usernameFound, hashFound, balanceFound)) return AccountStatus::NOT_EXISTS;

    if (usernameFound == username && bcrypt::validatePassword(password, hashFound)) {
        this->username = usernameFound;
        this->fileUsername = username;
        this->hashPassword = hashFound;
        this->tokens = balanceFound;
        this->logged = true;
        return AccountStatus::LOGGED;
    }
    else return AccountStatus::ERROR;
}

void Account::logout() {
    this->username = "";
    this->tokens = 0;
    this->logged = false;
}

bool Account::canBet(int amount) {
    return this->tokens >= amount;
}

void Account::applyResult(int bet, Result result) {
    switch (result) {
        case Result::BLACKJACK: tokens += static_cast<int>(bet * 1.5f); break;
        case Result::WIN:       tokens += bet;                          break;
        case Result::LOSE:      tokens -= bet;                          break;
        case Result::PUSH:
        default: break;
    }
}

AccountStatus Account::save() {
    std::string oldPath = this->accountDir + "/" + this->fileUsername + ".acc";
    std::string newPath = this->accountDir + "/" + this->username + ".acc";

    if (!std::filesystem::exists(oldPath)) return AccountStatus::NOT_EXISTS;

    if (this->fileUsername != this->username) {
        if (std::filesystem::exists(newPath))
            return AccountStatus::EXISTS;

        std::error_code ec;
        std::filesystem::rename(oldPath, newPath, ec);
        if (ec) return AccountStatus::ERROR;

        this->fileUsername = this->username;
    }
    
    std::ofstream file(newPath);
    if (!file) return AccountStatus::ERROR;

    file << PATTERN_USERNAME << this->username << "\n";
    file << PATTERN_PASSWORD << this->hashPassword << "\n";
    file << PATTERN_TOKENS  << this->tokens << "\n";
    file.close();

    return AccountStatus::SAVED;
}
