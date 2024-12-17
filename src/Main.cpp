#pragma once

#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/InputManager.h"
#include "../include/Global.h"
#include "../include/Animation.h"
#include "../include/GameEngine.h"

using namespace std;

//class Object : public InputManager::Listener {
//private:
//    Animation* cur = nullptr;
//    Vector2 position;
//    Vector2 size;
//    Texture& texture;
//    Vector2 velocity;
//    Vector2 acceleration;
//    Vector2 maxSpeed;
//    const float gravity = 1200.f;
//    const float jumpForce = 900.0f;
//    bool isJumping;
//    bool horizontalOrientation = true; //true = right, false = left
//
//    InputManager& inputManager; // Thêm đối tượng InputManager
//
//public:
//    Object(Vector2 position, Vector2 size, Texture& texture, InputManager& inputMgr)
//        : position(position), size(size), texture(texture), inputManager(inputMgr) {
//        velocity = Vector2(0, 0);
//        maxSpeed = Vector2(1000, 600);
//        acceleration = Vector2(1000, 500);
//        isJumping = false;
//
//        inputManager.addListener(*this);  // Đăng ký Object làm listener
//        cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
//        this->size = cur->getSize();
//        this->position.y = 800.f - this->size.y;
//        cur->reset();
//    }
//
//    ~Object() {
//        inputManager.removeListener(*this);  // Xóa listener khi Object bị hủy
//    }
//
//    void onKey(KeyboardKey key, bool pressed) override {
//        //Xử lí các nút bấm có tính năng đặc biệt (bắn lửa, )
//    }
//
//    void update(float deltaTime) {
//        // Gia tốc hãm
//        const float deceleration = 2000.0f; // Gia tốc hãm (pixel/s^2)
//        cur->update(deltaTime);
//        // Di chuyển theo trục X
//        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {  // Nhấn D (phải) nhưng không nhấn A (trái)
//            if (velocity.x < 0) {  // Đang di chuyển sang trái, hãm lại
//                if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
//                velocity.x += deceleration * deltaTime;
//                if (velocity.x > 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
//            }
//            else {
//                velocity.x += acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi phải
//                if (isJumping == false) {
//                    cur = RESOURCE_MANAGER.getAnimation("superluigi_walk_right");
//                    this->size = cur->getSize();
//                    if (velocity.x >= maxSpeed.x) {
//                        cur = RESOURCE_MANAGER.getAnimation("superluigi_run_right");
//                        this->size = cur->getSize();
//                    }
//                }
//            }
//        }
//        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {  // Nhấn A (trái) nhưng không nhấn D (phải)
//            if (velocity.x > 0) {  // Đang di chuyển sang phải, hãm lại
//                if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
//                velocity.x -= deceleration * deltaTime;
//                if (velocity.x < 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
//            }
//            else {
//                velocity.x -= acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi trái
//                if (isJumping == false) {
//                    cur = RESOURCE_MANAGER.getAnimation("superluigi_walk_left");
//                    this->size = cur->getSize();
//                    if (abs(velocity.x) >= maxSpeed.x) {
//                        cur = RESOURCE_MANAGER.getAnimation("superluigi_run_left");
//                        this->size = cur->getSize();
//                    }
//                }
//            }
//            
//        }
//        else { // Không nhấn phím di chuyển nào
//            if (velocity.x > 0) {
//                velocity.x -= deceleration * deltaTime;
//                if (velocity.x < 0) velocity.x = 0;
//                if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
//            }
//            else if (velocity.x < 0) {
//                velocity.x += deceleration * deltaTime;
//                if (velocity.x > 0) velocity.x = 0;
//                if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
//            }
//        }
//
//        if (velocity.x > 0) horizontalOrientation = true;
//        else if (velocity.x < 0) horizontalOrientation = false;
//
//        // Kiểm tra nhảy khi nhấn phím SPACE và đang không nhảy
//        if (IsKeyDown(KEY_SPACE) && !isJumping) {
//            velocity.y = -jumpForce;  // Đẩy lên
//            isJumping = true;  // Đánh dấu là đang nhảy
//            PlaySound(*RESOURCE_MANAGER.getSound("jump.wav"));
//        }
//
//        // Gia tốc trọng trường
//        else if (isJumping) {
//            velocity.y += gravity * deltaTime; // Gia tốc trọng trường tác động
//            // Kiểm tra đối tượng đã chạm mặt đất chưa
//            if (onGround()) {
//                position.y = 800.f - size.y;  // Giới hạn trên mặt đất
//                velocity.y = 0;  // Dừng chuyển động dọc trục Y
//                isJumping = false;  // Không còn nhảy nữa
//            }
//        }
//
//        // Giới hạn vận tốc (max speed)
//        if (fabs(velocity.x) > maxSpeed.x) {
//            velocity.x = (velocity.x > 0) ? maxSpeed.x : -maxSpeed.x;
//        }
//
//        if (isJumping) {
//            if (horizontalOrientation) cur = RESOURCE_MANAGER.getAnimation("superluigi_jump_right");
//            else cur = RESOURCE_MANAGER.getAnimation("superluigi_jump_left");
//            this->size = cur->getSize();
//        }
//
//        if (isIdle() && !isJumping) {
//            if (horizontalOrientation) cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
//            else cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
//            this->size = cur->getSize();
//        }
//
//        // Cập nhật vị trí mới
//        position.x += velocity.x * deltaTime;
//        position.y += velocity.y * deltaTime;
//
//        this->size = cur->getSize();
//    }
//
//    void draw() const {
//        //Rectangle destRect = { position.x, position.y, size.x, size.y };
//        //Rectangle srcRect = { 0, 0, (isFlipped ? -texture.width : texture.width), texture.height };
//        //DrawTexturePro(texture, srcRect, destRect, { 0, 0 }, 0.f, WHITE); // Vẽ texture
//        cur->render(position);
//    }
//
//    const Rectangle getRectangle() const {
//        return { position.x, position.y, size.x, size.y };
//    }
//
//    bool onGround() const {
//        if (position.y + size.y >= 800.f) return true;
//        return false;
//    }
//
//    bool isIdle() const {
//        return (velocity.x == 0.f && velocity.y == 0.f);
//    }
//};

//int main() {
//    InitAudioDevice();
//    InitWindow(1280, 800, "Super Mario Bros");
//    
//    RESOURCE_MANAGER.loadAllResource();
//    INPUT_MANAGER.bindKey(KEY_A);
//    INPUT_MANAGER.bindKey(KEY_D);
//    INPUT_MANAGER.bindKey(KEY_S);
//    INPUT_MANAGER.bindKey(KEY_SPACE);
//    INPUT_MANAGER.bindKey(KEY_LEFT_SHIFT);
//
//    // Tải texture cho vật thể
//    Texture2D texture = LoadTexture("../SuperMario/images.png");
//
//    // Tạo một vật thể với texture và InputManager
//    Object object(Vector2{ 0, 750 }, Vector2{ 0, 0 }, texture, INPUT_MANAGER);
//
//
//    RESOURCE_MANAGER.playMusic("World1.mp3");
//
//    while (!WindowShouldClose()) {
//        if (FPS_MANAGER.update()) {
//            // Update music stream
//            UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));
//
//            BeginDrawing();
//            ClearBackground(GRAY);
//
//            // Vẽ vật thể
//            float deltaTime = GetFrameTime();
//            //inputManager.update();
//            object.update(deltaTime);
//            object.draw();
//
//            EndDrawing();
//        }
//    }
//    CloseWindow();
//    CloseAudioDevice();
//
//    return 0;
//}
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
    Object object(Vector2{ 0, 750 }, Vector2{ 0, 0 }, texture, INPUT_MANAGER);
    RESOURCE_MANAGER.playMusic("World1.mp3");

    Map map1;
    map1.loadFromFile("../assets/Map/Map1-1.txt");
    map1.loadBackground("../assets/Map/Map1-1.png");

    GameEngine engine((float)1280, (float)800, (float)2779, (float)512, map1,object);
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
