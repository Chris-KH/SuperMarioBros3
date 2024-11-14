#include <iostream>
#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/Entity.h"

using namespace std;

int main() {
    InitWindow(800, 600, "Entity Class with Keyboard Movement");
    SetTargetFPS(120);

    // Tải texture cho vật thể
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo một vật thể với texture và tốc độ di chuyển là 200 pixels/second
    Entity entity(Vector2{ 100, 100 }, Vector2{ 100, 100 }, texture, 200.0f);

    while (!WindowShouldClose()) {
        entity.handleInput();

        entity.move();

        BeginDrawing();
        ClearBackground(GRAY);

        // Vẽ vật thể
        entity.draw();

        EndDrawing();
    }

    // Giải phóng tài nguyên
    entity.unloadTexture();
    CloseWindow();

    return 0;
}

//D:/Project/CS202/SuperMario/SuperMario/images.png