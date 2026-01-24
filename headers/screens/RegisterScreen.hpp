#pragma once

#include <raylib.h>
#include <string>
#include "screens/Screen.hpp"
#include "game_settings.hpp"

class RegisterScreen: public Screen {
    private:
        std::string message = "Register Screen";
    public:
        void draw();
        ScreenType changeScreen() { return ScreenType::NONE; }
};
