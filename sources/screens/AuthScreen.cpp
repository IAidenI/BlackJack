#include "screens/AuthScreen.hpp"

AuthScreen::AuthScreen() {
    this->loginButton.onClick([this]() {
        this->requestedScreen = ScreenType::LOGIN_SCREEN;
    });

    this->registerButton.onClick([this]() {
        this->requestedScreen = ScreenType::REGISTER_SCREEN;
    });
}

void AuthScreen::draw() {
    this->loginButton.draw();
    this->registerButton.draw();
    
    Vector2 mousePos = GetMousePosition();
    this->loginButton.update(mousePos);
    this->registerButton.update(mousePos);
}
