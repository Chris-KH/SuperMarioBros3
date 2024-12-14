#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/InputManager.h"
#include "../include/Global.h"
#include "../include/Animation.h"
#include "../include/GameEngine.h"
#include "../include/Mario.h"
#include "../include/Luigi.h"
using namespace std;


int main() {
    InitAudioDevice();
    InitWindow(1280, 800, "Super Mario Bros");
    
    RESOURCE_MANAGER.loadAllResource();
    INPUT_MANAGER.bindKey(KEY_A);
    INPUT_MANAGER.bindKey(KEY_D);
    INPUT_MANAGER.bindKey(KEY_S);
    INPUT_MANAGER.bindKey(KEY_SPACE);
    INPUT_MANAGER.bindKey(KEY_LEFT_SHIFT);
    registerBlocks();
    // Tải texture cho vật thể
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo một vật thể với texture và InputManager
    Character* player = new Mario(Vector2{1,1});
    RESOURCE_MANAGER.playMusic("World1.mp3");

    Map map1;
    map1.loadFromFile("../assets/Map/Map1-1.txt");
    map1.loadBackground("../assets/Map/Map1-1.png");

    GameEngine engine((float)1280, (float)800, (float)2779, (float)512, map1,player);
    engine.run();
    //while (!WindowShouldClose()) {
    //    if (FPS_MANAGER.update()) {
    //       // Update music stream
    //        UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));

    //       BeginDrawing();
    //        ClearBackground(GRAY);
    //       map1.renderBackground();


    //      // Vẽ vật thể
    //        float deltaTime = GetFrameTime();
    //        //inputManager.update();
    //        object.update(deltaTime);
    //        object.draw();
    //      map1.renderAllBlock();

    //       EndDrawing();
    //    }
    //}

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
