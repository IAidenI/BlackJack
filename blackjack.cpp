#include "game.hpp"
#include "account.hpp"

int main() {
	Game game;
	Account user;
	std::string choice = "";
	std::string errorMsg = "";
	std::string succesMsg = "";

	game.clearScreen();

	while (true) {
		if (!errorMsg.empty()) {
			game.clearScreen();
			std::cout << "[ ERROR ] " << errorMsg << "\n\n";
			errorMsg.clear();
		}

		if (!succesMsg.empty()) {
			game.clearScreen();
			std::cout << "[ SUCCES ] " << succesMsg << "\n\n";
			succesMsg.clear();
		}

		if (user.isConnected()) {
			std::cout << "[ STATUS ] - Connecté\n";
			std::cout << "[  INFOS ] nom : " << user.getUsername() << "\n";
			std::cout << "           argent : " << user.getBalance() << "\n\n";
			std::cout << "[1] - Changer le nom d'utilisateur\n";
			std::cout << "[2] - Changer le mot de passe\n";
			std::cout << "[3] - Se déconnecter\n";
			std::cout << "[4] - Supprimer le compte\n";
			std::cout << "[5] - Jouer\n";
			std::cout << "[6] - Exit\n";
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
				std::cout << "Saisissez votre ancien mot de passe : ";
				std::string oldPassword;
				std::cin >> oldPassword;

				if (!user.isPasswordCorrect(oldPassword)) {
					errorMsg = "Mot de passe incorrect";
					continue;
				}

				std::cout << "Saisissez le nouveau mot de passe : ";
				std::string newPassword;
				std::cin >> newPassword;

				user.changePassword(newPassword);
				AccountStatus ret = user.save();

				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else succesMsg = "Mot de passe mis à jour";
			}
			else if (choice == "3") {
				user.logout();
				game.clearScreen();
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
			}
			else if (choice == "5") {
				int bet = 0;
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
						std::cout << "Solde insuffisant.\n";
						continue;
					}

					break;
				}

				std::cout << "Vous misez : " << bet << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				game.start();

				int gain = 0;
				switch (game.getStatus()) {
					case GameStatus::PLAYER_WIN_WITH_BJ: {
						std::cout << "Vous avez gagné !\n\n";
						gain = static_cast<int>(bet * 1.5f);
						user.applyResult(bet, Result::BLACKJACK);
						break;
					}
					case GameStatus::PLAYER_WIN: {
						std::cout << "Vous avez gagné !\n\n";
        				gain = bet;
						user.applyResult(bet, Result::WIN);
						break;
					}
					case GameStatus::DEALER_WIN: {
						std::cout << "Le croupier a gagné !\n\n";
						gain = -bet;
						user.applyResult(bet, Result::LOSE);
						break;
					}
					case GameStatus::PUSH: {
						std::cout << "Égalité !\n\n";
						gain = 0;
						user.applyResult(bet, Result::PUSH);
						break;
					}
					default: {
						std::cout << "Le jeu s'est terminé de manière inattendue.\n\n";
						break;
					}
				}


				std::cout << "\nAppuyez sur Entrée pour revenir au menu...";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
				game.clear();
				
				if (gain > 0) succesMsg = "Vous avez gagné : " + std::to_string(gain);
				else if (gain < 0) succesMsg = "Vous avez perdu : " + std::to_string(-gain);
				else succesMsg = "Aucun gain";
			}
			else if (choice == "6") return 0;
			else errorMsg = "[!] Option inconnu";
		}
		else {
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

				std::cout << "Saisissez un mot de passe : ";
				std::string password = "";
				std::cin >> password;

				AccountStatus ret = user.create(username, password);
				if (ret == AccountStatus::ERROR) errorMsg = "Une erreur est survenu";
				else if (ret == AccountStatus::EXISTS) errorMsg = "L'utilisateur existe déjà";
				else succesMsg = "Utilisateur crée";
			} else if (choice == "2") {
				std::cout << "Saisissez votre nom d'utilisateur : ";
				std::string username = "";
				std::cin >> username;

				std::cout << "Saisissez votre mot de passe : ";
				std::string password = "";
				std::cin >> password;

				AccountStatus ret = user.login(username, password);
				if (ret == AccountStatus::ERROR) errorMsg = "Nom d'utilisateur ou mot de passe incorrect";
				else if (ret == AccountStatus::NOT_EXISTS) errorMsg = "L'utilisateur n'existe pas";
				else game.clearScreen();
			} else if (choice == "3") return 0;
			else errorMsg = "[!] Option inconnu";
		}
	}

	return 0;
}
