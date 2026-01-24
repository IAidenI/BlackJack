#pragma once

#include <raylib.h>
#include <string>
#include "screens/Screen.hpp"
#include "game_settings.hpp"

class LoginScreen: public Screen {
    private:
        std::string message = "Login Screen";
    public:
        void draw();
        ScreenType changeScreen() { return ScreenType::NONE; }
};
