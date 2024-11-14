#include <iostream>
#include <raylib.h>
#include "../include/Strategy.h"
#include "../include/Entity.h"
//#include "../lib/bits/stdc++.h"

using namespace std;

int main() {
    // Initialize raylib and set up the window
    InitWindow(800, 600, "Strategy Pattern Collision with Movement");
    SetTargetFPS(60);
    // Create an entity and a block
    Entity player(100, 100, 50, 50, 200.0f);  // 200 pixels per second speed
    Block wall(200, 100, 50, 50);

    // Create a collision strategy and assign it to the entity
    EntityToBlockPushbackCollision pushbackCollision;
    EntityToBLockCollision normalCollision;
    player.setCollisionStrategy(&normalCollision);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();  // Time elapsed since the last frame

        // Move the player
        player.move(deltaTime);

        // Check for collision
       bool isColliding = player.checkCollision(wall);

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(player.hitbox, isColliding ? RED : BLUE);
        DrawRectangleRec(wall.hitbox, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}



