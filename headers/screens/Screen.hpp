#pragma once

enum class ScreenType {
    AUTH_SCREEN,
    LOGIN_SCREEN,
    REGISTER_SCREEN,
    NONE
};

class Screen {
    public:
        virtual ~Screen() = default;

        virtual void draw() = 0;
        virtual ScreenType changeScreen() = 0;
};
