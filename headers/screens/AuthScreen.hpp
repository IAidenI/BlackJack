#pragma once

#include <raylib.h>
#include <string>
#include "screens/Screen.hpp"
#include "game_settings.hpp"
#include "widgets.hpp"

class AuthScreen: public Screen {
    private:
        Button loginButton = Button("Login", { (float)(SCREEN_WIDTH / 2 - 50), (float)(SCREEN_HEIGHT / 2 + 30), 100.0f, 40.0f }, LIGHTGRAY);
        Button registerButton = Button("Register", { (float)(SCREEN_WIDTH / 2 - 50), (float)(SCREEN_HEIGHT / 2 + 80), 100.0f, 40.0f }, LIGHTGRAY);
        ScreenType requestedScreen  = ScreenType::NONE;
    public:
        AuthScreen();
        void draw();
        ScreenType changeScreen() { return this->requestedScreen; };
};
