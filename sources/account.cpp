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
    file << PATTERN_USERNAME       << username                       << "\n";
    file << PATTERN_PASSWORD       << hash                           << "\n";
    file << PATTERN_TOKENS         << std::to_string(DEFAULT_TOKENS) << "\n";
    file << PATTERN_LOAN_ACTIVE    << "0\n";
    file << PATTERN_LOAN_TYPE      << "SMALL\n";
    file << PATTERN_LOAN_REMAINING << "0\n";
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

bool Account::loadAccountFile(std::string path, std::string& username, std::string& hash, int& tokens, ActiveLoan& loan) {
    std::ifstream file(path);
    if (!file) return false;

    bool hasUser = false, hasHash = false, hasTokens = false;
    bool hasLoanActive = false, hasLoanType = false, hasLoanRemaining = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind(PATTERN_USERNAME, 0) == 0) {
            username = line.substr(std::string(PATTERN_USERNAME).size());
            hasUser = !username.empty();
        }
        else if (line.rfind(PATTERN_PASSWORD, 0) == 0) {
            hash = line.substr(std::string(PATTERN_PASSWORD).size());
            hasHash = !hash.empty();
        }
        else if (line.rfind(PATTERN_TOKENS, 0) == 0) {
            tokens = std::stoi(line.substr(std::string(PATTERN_TOKENS).size()));
            hasTokens = true;
        }
        else if (line.rfind(PATTERN_LOAN_ACTIVE, 0) == 0) {
            loan.active = std::stoi(line.substr(std::string(PATTERN_LOAN_ACTIVE).size())) != 0;
            hasLoanActive = true;
        }
        else if (line.rfind(PATTERN_LOAN_TYPE, 0) == 0) {
            loan.type = loanTypeFromString(line.substr(std::string(PATTERN_LOAN_TYPE).size()));
            hasLoanType = true;
        }
        else if (line.rfind(PATTERN_LOAN_REMAINING, 0) == 0) {
            loan.remaining = std::stoi(line.substr(std::string(PATTERN_LOAN_REMAINING).size()));
            hasLoanRemaining = true;
        }
    }
    
    if (!(hasLoanActive && hasLoanType && hasLoanRemaining)) {
        loan.active = false;
        loan.type = LoanType::SMALL;
        loan.remaining = 0;
    }
    
    return hasUser && hasHash && hasTokens;
}

AccountStatus Account::login(std::string username, std::string password) {
    std::string filePath = this->accountDir + "/" + username + ".acc";

    if (!std::filesystem::exists(filePath)) return AccountStatus::NOT_EXISTS;

    std::string usernameFound = "";
    std::string hashFound = "";
    int tokensFound = 0;
    ActiveLoan loanFound;
    if (!this->loadAccountFile(filePath, usernameFound, hashFound, tokensFound, loanFound)) return AccountStatus::NOT_EXISTS;

    if (usernameFound == username && bcrypt::validatePassword(password, hashFound)) {
        this->username = usernameFound;
        this->fileUsername = username;
        this->hashPassword = hashFound;
        this->tokens = tokensFound;
        this->loan = loanFound;
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

    file << PATTERN_USERNAME       << this->username                    << "\n";
    file << PATTERN_PASSWORD       << this->hashPassword                << "\n";
    file << PATTERN_TOKENS         << this->tokens                      << "\n";
    file << PATTERN_LOAN_ACTIVE    << (this->loan.active ? "1" : "0")   << "\n";
    file << PATTERN_LOAN_TYPE      << loanTypeToString(this->loan.type) << "\n";
    file << PATTERN_LOAN_REMAINING << this->loan.remaining              << "\n";
    file.close();

    return AccountStatus::SAVED;
}
