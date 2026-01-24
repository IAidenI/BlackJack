#include <raylib.h>

#include "game.hpp"

int main() {    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Blackjack");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("BlackJack", 190, 200, 20, BLACK);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}