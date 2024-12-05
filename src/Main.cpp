#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/Entity.h"
#include "../include/Block.h"
#include "../include/Collision.h"
#include "../include/Map.h"
#include "../include/Menu.h"



using namespace std;

int main() {
    InitWindow(1280, 800, "entity class with keyboard movement");
    SetTargetFPS(60);

    //// tải texture cho vật thể
 Texture2D texture = LoadTexture("../supermario/images.png");

Floor f1({ 200,500 }, { 900, 300 }, GREEN);



    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Vẽ vật thể
         f1.draw();
        //..DrawRectangleRec(wall.GetHitbox(), DARKGRAY);
       //DrawRectangleRec(wall.GetHitbox(), DARKGRAY);

       ClearBackground(Color(100, 100, 100, 100));
       DrawText("Mario Super Bros", 100, 100, 40, ORANGE);
        EndDrawing();
    }
    CloseWindow();
    //Menu mn;
   //mn.run();

    return 0;
}

