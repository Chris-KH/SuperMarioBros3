//#include <iostream>
//#include <raylib.h>
//#include "../include/Strategy.h"
//#include "../include/Entity.h"
////#include "../lib/bits/stdc++.h"
//
//using namespace std;
//
//int main() {
//    // Initialize raylib and set up the window
//    InitWindow(800, 600, "Strategy Pattern Collision with Movement");
//    SetTargetFPS(60);
//    // Create an entity and a block
//    Entity player(100, 100, 50, 50, 200.0f);  // 200 pixels per second speed
//    Block wall(200, 100, 50, 50);
//
//    // Create a collision strategy and assign it to the entity
//    EntityToBlockPushbackCollision pushbackCollision;
//    EntityToBLockCollision normalCollision;
//    player.setCollisionStrategy(&normalCollision);
//
//    // Game loop
//    while (!WindowShouldClose()) {
//        float deltaTime = GetFrameTime();  // Time elapsed since the last frame
//
//        // Move the player
//        player.move(deltaTime);
//
//        // Check for collision
//       bool isColliding = player.checkCollision(wall);
//
//        // Begin drawing
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        DrawRectangleRec(player.getHitbox(), isColliding ? RED : BLUE);
//        DrawRectangleRec(wall.getHitbox(), DARKGRAY);
//
//        EndDrawing();
//    }
//
//    CloseWindow();
//
//    return 0;
//}


#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/Entity.h"

using namespace std;

int main() {
    InitWindow(1280, 800, "Entity Class with Keyboard Movement");
    SetTargetFPS(60);

    // Tải texture cho vật thể
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo một vật thể với texture và tốc độ di chuyển là 200 pixels/second
    Entity entity(Vector2{ 100, 100 }, Vector2{ 100, 100 }, texture, 300.0f);

    //Block wall(200, 100, 50, 50);
    EntityToBlockPushbackCollision pushbackCollision;
    EntityToBLockCollision normalCollision;
    entity.setCollisionStrategy(&pushbackCollision);

    while (!WindowShouldClose()) {
        entity.handleInput();

        entity.move();
        //bool isColliding = entity.checkCollision(wall);
        BeginDrawing();
        ClearBackground(GRAY);

        // Vẽ vật thể

        entity.draw();
        //DrawRectangleRec(wall.getHitbox(), DARKGRAY);
        
        
        //ClearBackground(Color(100, 100, 100, 100));
        DrawText("MARIO SUPER BROS", 100, 100, 40, ORANGE);


        EndDrawing();
    }

    // Giải phóng tài nguyên
    entity.unloadTexture();
    CloseWindow();

    return 0;
}

