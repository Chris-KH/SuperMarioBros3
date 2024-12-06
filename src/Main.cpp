#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"
#include "../include/InputManager.h"
#include "../include/Global.h"
#include "../include/Animation.h"

using namespace std;

class Object : public InputManager::Listener {
private:
    Animation* cur = nullptr;
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

    InputManager& inputManager; // Thêm đối tượng InputManager

public:
    Object(Vector2 position, Vector2 size, Texture& texture, InputManager& inputMgr)
        : position(position), size(size), texture(texture), inputManager(inputMgr) {
        velocity = Vector2(0, 0);
        maxSpeed = Vector2(600, 600);
        acceleration = Vector2(500, 500);
        isFlipped = false;
        isJumping = false;

        inputManager.addListener(*this);  // Đăng ký Object làm listener
    }

    ~Object() {
        inputManager.removeListener(*this);  // Xóa listener khi Object bị hủy
    }

    void onKey(KeyboardKey key, bool pressed) override {
        //Xử lí các nút bấm có tính năng đặc biệt (bắn lửa, )
    }

    void update(float deltaTime) {
        // Gia tốc hãm
        const float deceleration = 1000.0f; // Gia tốc hãm (pixel/s^2)
        cur = RESOURCE_MANAGER.getAnimation("marioRun");
        cur->update(deltaTime);
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
            PlaySound(*RESOURCE_MANAGER.getSound("jump.wav"));
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
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }

    void draw() const {
        //Rectangle destRect = { position.x, position.y, size.x, size.y };
        //Rectangle srcRect = { 0, 0, (isFlipped ? -texture.width : texture.width), texture.height };
        //DrawTexturePro(texture, srcRect, destRect, { 0, 0 }, 0.f, WHITE); // Vẽ texture
        cur->render(position, false, false, 2.f);
    }

    const Rectangle getRectangle() const {
        return { position.x, position.y, size.x, size.y };
    }
};

int main() {
    InitAudioDevice();
    InitWindow(1280, 800, "Super Mario Bros");
    
    RESOURCE_MANAGER.loadAllResource();

    // Tải texture cho vật thể
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo InputManager
    InputManager inputManager;
    inputManager.bindKey(KEY_A);
    inputManager.bindKey(KEY_D);
    inputManager.bindKey(KEY_S);
    inputManager.bindKey(KEY_SPACE);

    // Tạo một vật thể với texture và InputManager
    Object object(Vector2{ 0, 700 }, Vector2{ 100, 100 }, texture, inputManager);


    RESOURCE_MANAGER.playMusic("World1.mp3");

    while (!WindowShouldClose()) {
        if (FPS_MANAGER.update()) {
            // Update music stream
            UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));

            BeginDrawing();
            ClearBackground(GRAY);

            // Vẽ vật thể
            float deltaTime = GetFrameTime();
            //inputManager.update();
            object.update(deltaTime);
            object.draw();

            EndDrawing();
        }
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
