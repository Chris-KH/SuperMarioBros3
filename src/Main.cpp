#include <iostream>
#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"

using namespace std;

int main() {
    std::cout << "Starting the game..." << "\n";
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Super Mario Bros!");
    SetTargetFPS(60);

    Font font = LoadFontEx("", 64, 0, 0); // input font file, download from internet

    Texture2D background = LoadTexture("");// input background file


    while (WindowShouldClose() == false) {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        

        BeginDrawing();
        
        
        //ClearBackground(Color(100, 100, 100, 100));
        DrawText("MARIO SUPER BROS", 100, 100, 40, ORANGE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}