#include "widgets.hpp"

Button::Button(std::string message, Rectangle rect, Color color) {
    this->message = message;
    this->rect = rect;
    this->color = color;
}

void Button::draw() {
    DrawRectangleRec(this->rect, this->color);
    int fontSize = 20;
    int textWidth = MeasureText(this->message.c_str(), fontSize);
    DrawText(this->message.c_str(), static_cast<int>(this->rect.x + (this->rect.width - textWidth) / 2), static_cast<int>(this->rect.y + (this->rect.height - fontSize) / 2), fontSize, BLACK);

}

void Button::update(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, this->rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (this->callback) this->callback();
    }
}
