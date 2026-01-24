#include "screens/RegisterScreen.hpp"

void RegisterScreen::draw() {
    int fontSize = 20;
    int textWidth = MeasureText(this->message.c_str(), fontSize);
    DrawText(this->message.c_str(), static_cast<int>((SCREEN_WIDTH - textWidth) / 2), static_cast<int>(SCREEN_HEIGHT / 2), fontSize, BLACK);
}
