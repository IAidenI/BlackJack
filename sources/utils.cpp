#include "utils.hpp"

int getch() {
    int ch;
    // struct to hold the terminal settings
    struct termios old_settings, new_settings;
    // take default setting in old_settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // make of copy of it (Read my previous blog to know 
    // more about how to copy struct)
    new_settings = old_settings;
    // change the settings for by disabling ECHO mode
    // read man page of termios.h for more settings info
    new_settings.c_lflag &= ~(ICANON | ECHO);
    // apply these new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    // now take the input in this mode
    ch = getchar();
    // reset back to default settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}

std::string ReadPassword(std::string message) {
    std::cout << message;

    std::string password;
    int ch;
    while ((ch = getch()) != '\n' && ch != '\r' && ch != EOF) {
        if (ch == 127 || ch == 8) { // handle backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else {
            password.push_back(static_cast<char>(ch));
            // echo the '*' to get feel of taking password 
            std::cout << "*" << std::flush;
        }
    }
    std::cout << "\n";

    return std::string(password);
}

void clearScreen() {
    std::cout << "\033[2J\033[H";
}
