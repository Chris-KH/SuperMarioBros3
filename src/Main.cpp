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
#include "../include/Block.h"

using namespace std;

class Object {
private:
    Vector2 position;
    Vector2 size;
    Texture& texture;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 maxSpeed;
    const float gravity = 1200.f;
    const float jumpForce = 900.0f;
    bool isFlipped;
    bool isJumping;
    const float groundY = 700.f;
public:
    Object(Vector2 position, Vector2 size, Texture& texture)
        : position(position),
        size(size),
        texture(texture) {
        velocity = Vector2(0, 0);
        maxSpeed = Vector2(600, 600);
        acceleration = Vector2(500, 500);
        isFlipped = false;
        isJumping = false;
    }

    void update(float deltaTime) {
        // Gia tốc hãm
        const float deceleration = 1000.0f; // Gia tốc hãm (pixel/s^2)

        // Di chuyển theo trục X
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {  // Nhấn D (phải) nhưng không nhấn A (trái)
            if (velocity.x < 0) {  // Đang di chuyển sang trái, hãm lại
                velocity.x += deceleration * deltaTime;
                if (velocity.x > 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
            }
            else {
                velocity.x += acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi phải
            }
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {  // Nhấn A (trái) nhưng không nhấn D (phải)
            if (velocity.x > 0) {  // Đang di chuyển sang phải, hãm lại
                velocity.x -= deceleration * deltaTime;
                if (velocity.x < 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
            }
            else {
                velocity.x -= acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi trái
            }
        }
        else { // Không nhấn phím di chuyển nào
            if (velocity.x > 0) {
                velocity.x -= deceleration * deltaTime;
                if (velocity.x < 0) velocity.x = 0;
            }
            else if (velocity.x < 0) {
                velocity.x += deceleration * deltaTime;
                if (velocity.x > 0) velocity.x = 0;
            }
        }

        // Kiểm tra nhảy khi nhấn phím SPACE và đang không nhảy
        if (IsKeyDown(KEY_SPACE) && !isJumping && abs(position.y - groundY) < 1e-9) {
            velocity.y = -jumpForce;  // Đẩy lên
            isJumping = true;  // Đánh dấu là đang nhảy
        }

        // Gia tốc trọng trường
        else if (isJumping) {
            velocity.y += gravity * deltaTime; // Gia tốc trọng trường tác động
            // Kiểm tra đối tượng đã chạm mặt đất chưa
            if (position.y >= groundY) {
                position.y = groundY;  // Giới hạn trên mặt đất
                velocity.y = 0;  // Dừng chuyển động dọc trục Y
                isJumping = false;  // Không còn nhảy nữa
            }
        }

        

        // Giới hạn vận tốc (max speed)
        if (fabs(velocity.x) > maxSpeed.x) {
            velocity.x = (velocity.x > 0) ? maxSpeed.x : -maxSpeed.x;
        }

        if (velocity.x < 0) isFlipped = true;
        else if (velocity.x > 0) isFlipped = false;

        // Cập nhật vị trí mới
        setPosition(Vector2(getPosition().x + velocity.x * deltaTime, getPosition().y + velocity.y * deltaTime));
    }



    Vector2 getVelocity() const { return velocity; }

    void setVelocity(Vector2 vel) { velocity = vel; }

    Vector2 getAcceleration() const { return acceleration; }

    void setAcceleration(Vector2 acc) { acceleration = acc; }

    Vector2 getMaxSpeed() const { return maxSpeed; }

    void setMaxSpeed(Vector2 max) { maxSpeed = max; }

    float getX() const { return position.x; }

    float getY() const { return position.y; }

    float getWidth() const { return size.x; }

    float getHeight() const { return size.y; }

    Rectangle getRectangle() const {
        return { position.x, position.y, size.x, size.y };
    }

    Vector2 getSize() const {
        return this->size;
    }

    Vector2 getPosition() const {
        return this->position;
    }

    void setPosition(Vector2 pos) { position = pos; }

    void setSize(Vector2 sz) { size = sz; }

    

    void draw() const {
        Rectangle destRect = { getPosition().x, getPosition().y, getSize().x, getSize().y };
        Rectangle srcRect = { 0, 0, (isFlipped ? -texture.width : texture.width), texture.height };
        DrawTexturePro(texture, srcRect, destRect, {0, 0}, 0.f, WHITE); // Replace with texture drawing
    }
};

int main() {
    InitWindow(1280, 800, "Entity Class with Keyboard Movement");
    SetTargetFPS(60);

    // Tải texture cho vật thể
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo một vật thể với texture và tốc độ di chuyển là 200 pixels/second
    Object object(Vector2{ 0, 700 }, Vector2{ 100, 100 }, texture);

    //Block wall(200, 100, 50, 50, normal);
    //EntityToBlockPushbackCollision pushbackCollision;
    //EntityToBLockCollision normalCollision;
    //entity.setCollisionStrategy(&pushbackCollision);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        // Vẽ vật thể
        float deltaTime = GetFrameTime();
        object.update(deltaTime);
        object.draw();
        //DrawRectangleRec(wall.getHitbox(), DARKGRAY);
        //DrawRectangleRec(wall.getHitbox(), DARKGRAY);
        
        
        ClearBackground(Color(100, 100, 100, 100));
        //DrawText("MARIO SUPER BROS", 100, 100, 40, ORANGE);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

