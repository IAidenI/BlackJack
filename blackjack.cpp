#include "game.hpp"
#include "account.hpp"
#include "bank.hpp"
#include "utils.hpp"

int main() {
	Game game;
	Bank bank;
	Account user;
	std::string choice = "";
	std::string errorMsg = "";
	std::string succesMsg = "";

	clearScreen();

	while (true) {
		if (!errorMsg.empty()) {
			clearScreen();
			std::cout << "[ ERROR ] " << errorMsg << "\n\n";
			errorMsg.clear();
		}

		if (!succesMsg.empty()) {
			clearScreen();
			std::cout << "[ SUCCES ] " << succesMsg << "\n\n";
			succesMsg.clear();
		}

		if (user.isConnected()) {
			std::cout << "[ STATUS ] - Connecté\n";
			std::cout << "[  INFOS ] nom    : " << user.getUsername() << "\n";
			std::cout << "           jetons : " << user.getTokens() << "\n";
			if (user.hasActiveLoan()) {
				auto& loan = user.getLoan();
				std::cout << "[  LOAN  ] type       : " << loanTypeToString(loan.type) << "\n";
				std::cout << "           à payer    : " << loan.remaining << "\n\n";
			}
			std::cout << "[1] - Changer le nom d'utilisateur\n";
			std::cout << "[2] - Changer le mot de passe\n";
			std::cout << "[3] - Se déconnecter\n";
			std::cout << "[4] - Supprimer le compte\n";
			std::cout << "[5] - Faire un prêt\n";
			std::cout << "[6] - Jouer\n";
			std::cout << "[7] - Exit\n";
			std::cout << "[ choix ] : ";
			std::cin >> choice;

			if (choice == "1") {
				std::cout << "Saisissez votre nouveau nom d'utilisateur : ";
				std::string newUsername;
				std::cin >> newUsername;

				user.changeUsername(newUsername);

				AccountStatus ret = user.save();
				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else if (ret == AccountStatus::EXISTS) errorMsg = "Ce nom est déjà utilisé";
				else succesMsg = "Nom d'utilisateur mis à jour";
			}
			else if (choice == "2") {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::string oldPassword = ReadPassword("Saisissez votre ancien mot de passe : ");

				if (!user.isPasswordCorrect(oldPassword)) {
					errorMsg = "Mot de passe incorrect";
					continue;
				}

				std::string newPassword = ReadPassword("Saisissez le nouveau mot de passe : ");

				user.changePassword(newPassword);
				AccountStatus ret = user.save();

				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else succesMsg = "Mot de passe mis à jour";
			}
			else if (choice == "3") {
				user.logout();
				clearScreen();
			}
			else if (choice == "4") {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Voulez vous vraiment supprimer votre compte ? Cette action est irrévocable. (y/N) : ";

				std::string input;
				std::getline(std::cin, input);

				char confirm = 'n';
				if (!input.empty()) {
					confirm = static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));
				}

				if (confirm != 'y') {
					succesMsg = "Opération annulé";
					continue;
				}

				AccountStatus ret = user.remove();
				if (ret == AccountStatus::NOT_LOGGED) errorMsg = "Vous n'êtes pas connecté";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else succesMsg = "Compte supprimé";
			} else if (choice == "5") {
				if (user.hasActiveLoan()) {
					errorMsg = "Vous avez déjà un prêt actif";
					continue;
				}

				auto offers = bank.getLoanOffers();
				std::cout << "Offres de prêt disponibles :\n";

				for (size_t i = 0; i < offers.size(); ++i) {
					auto& offer = offers[i];
					std::cout << "[" << (i + 1) << "] - Montant        : " << offer.amount << " jetons\n";
					std::cout << "      Taux d'intérêt : " << static_cast<int>(offer.interestRate * 100) << "%\n";
					std::cout << "      Minimum requis : " << offer.minTokensRequired << " jetons\n\n";
				}

				int selected = -1;
				while (true) {
					std::cout << "Choisissez une offre de prêt (1-" << offers.size() << ") ou 0 pour annuler : ";
					std::string input;
					std::cin >> input;

					bool valid = !input.empty();
					for (char c : input) {
						if (!std::isdigit(static_cast<unsigned char>(c))) {
							valid = false;
							break;
						}
					}

					if (!valid) {
						std::cout << "Veuillez entrer un nombre valide.\n";
						continue;
					}

					int value = std::stoi(input);
					if (value == 0) break;
					if (value < 1 || value > static_cast<int>(offers.size())) {
						std::cout << "Choix invalide. Veuillez réessayer.\n";
						continue;
					}

					selected = value - 1;
					break;
				}

				if (selected == -1) {
					clearScreen();
					continue;
				}
				LoanType selectedType = offers[selected].type;

				if (!bank.requestLoan(user, selectedType)) errorMsg = "Impossible de contracter ce prêt";
				else {
					AccountStatus ret = user.save();
					if (ret == AccountStatus::ERROR) {
						user.getLoan().active = false;
						user.getLoan().remaining = 0;
						errorMsg = "Une erreur est survenue lors de la sauvegarde";
					} else {
						succesMsg = "Prêt accordé";
					}
				}
			}
			else if (choice == "6") {
				int bet = 0;
				bool cancel = false;
				while (true) {
					std::cout << "Entrez votre mise : ";
					std::string input;
					std::cin >> input;

					bool valid = !input.empty();
					for (char c : input) {
						if (!std::isdigit(static_cast<unsigned char>(c))) {
							valid = false;
							break;
						}
					}

					if (!valid) {
						std::cout << "Veuillez entrer un nombre valide.\n";
						continue;
					}

					bet = std::stoi(input);

					if (bet <= 0) {
						std::cout << "La mise doit être un entier positif.\n";
						continue;
					}

					if (!user.canBet(bet)) {
						errorMsg = "Solde insuffisant.";
						cancel = true;
						break;
					}

					break;
				}
				if (cancel) continue;

				user.addTokens(-bet);
				std::cout << "Vous misez : " << bet << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				game.start();

				int profit = 0;
				Result result = Result::LOSE;

				switch (game.getStatus()) {
					case GameStatus::PLAYER_WIN_WITH_BJ:
						profit = static_cast<int>(bet * 1.5f);
						result = Result::BLACKJACK;
						std::cout << "Vous avez gagné " << profit << " tokens !\n\n";
						break;

					case GameStatus::PLAYER_WIN:
						profit = bet;
						result = Result::WIN;
						std::cout << "Vous avez gagné " << profit << " tokens !\n\n";
						break;

					case GameStatus::DEALER_WIN:
						result = Result::LOSE;
						std::cout << "Le croupier a gagné !\n\n";
						break;

					case GameStatus::PUSH:
						result = Result::PUSH;
						std::cout << "Égalité !\n\n";
						break;

					default:
						std::cout << "Le jeu s'est terminé de manière inattendue.\n\n";
						break;
				}

				if (profit > 0 && bank.repay(user, profit)) {
					std::cout << "Un remboursement de votre prêt a été effectué, vous gagnez " << profit << " tokens.\n";
				}

				if (result == Result::WIN || result == Result::BLACKJACK) {
					user.addTokens(bet + profit);
				} else if (result == Result::PUSH) {
					user.addTokens(bet);
				}

				std::cout << "\nAppuyez sur Entrée pour revenir au menu...";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
				game.clear();
				
				AccountStatus ret = user.save();
				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else if (ret == AccountStatus::EXISTS) errorMsg = "Ce nom est déjà utilisé";
				else {
					if (result == Result::LOSE) succesMsg = "Vous avez perdu : " + std::to_string(bet);
					else if (result == Result::PUSH) succesMsg = "Égalité";
					else succesMsg = "Vous avez gagné : " + std::to_string(profit);
				}
			}
			else if (choice == "7") return 0;
			else errorMsg = "[!] Option inconnu";
		} else {
			std::cout << "[ STATUS ] - Déconnecté\n";
			std::cout << "[1] - Crée un compte\n";
			std::cout << "[2] - Se connecter\n";
			std::cout << "[3] - Exit\n";
			std::cout << "[ choix ] : ";
			std::cin >> choice;

			if (choice == "1") {
				std::cout << "Saisissez un nom d'utilisateur : ";
				std::string username = "";
				std::cin >> username;

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::string password = ReadPassword("Saisissez un mot de passe : ");

				AccountStatus ret = user.create(username, password);
				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::EXISTS) errorMsg = "L'utilisateur existe déjà";
				else succesMsg = "Utilisateur crée";
			} else if (choice == "2") {
				std::cout << "Saisissez votre nom d'utilisateur : ";
				std::string username = "";
				std::cin >> username;

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::string password = ReadPassword("Saisissez votre mot de passe : ");

				AccountStatus ret = user.login(username, password);
				if (ret == AccountStatus::ERROR) errorMsg = "Nom d'utilisateur ou mot de passe incorrect";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else clearScreen();
			} else if (choice == "3") return 0;
			else errorMsg = "[!] Option inconnu";
		}
	}

	return 0;
}
