#pragma once

#include <raylib.h>
#include <string>
#include <functional>

class Button {
    private:
        std::string message;
        Rectangle rect;
        Color color;
        std::function<void()> callback;
    public:
        Button(std::string message, Rectangle rect, Color color);

        void draw();
        void update(Vector2 mousePos);
        void onClick(std::function<void()> callback) { this->callback = callback; }
};
