#include <raylib.h>

#include "widgets.hpp"
#include "screens/screens.hpp"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Blackjack");

    SetTargetFPS(60);

    AuthScreen authScreen;
    LoginScreen loginScreen;
    RegisterScreen registerScreen;

    Screen* currentScreen = &authScreen;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            currentScreen->draw();

            ScreenType nextScreen = currentScreen->changeScreen();
            if (nextScreen == ScreenType::LOGIN_SCREEN) currentScreen = &loginScreen;
            if (nextScreen == ScreenType::REGISTER_SCREEN) currentScreen = &registerScreen;
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}