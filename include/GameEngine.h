#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Entity.h"
#include "Block.h"
#include "Collision.h"

class GameCamera {
public:
	float cameraX;
	float cameraY;
	float cameraWidth;
	float cameraHeight;
	float scale; // New: scaling factor

	RenderTexture2D renderTexture;

	GameCamera(float width, float height, int mapWidth, int mapHeight, float initialScale = 1.0f)
		: cameraWidth(width), cameraHeight(height), cameraX(0), cameraY(0), scale(initialScale) {
		renderTexture = LoadRenderTexture(mapWidth, mapHeight);
	}

	~GameCamera() {
		UnloadRenderTexture(renderTexture);
	}

	void update(float characterX, float characterY) {
		// Calculate scaled dimensions
		float scaledWidth = cameraWidth / scale;
		float scaledHeight = cameraHeight / scale;

		// Update the camera's position to center on the character
		cameraX = characterX - scaledWidth / 2;
		cameraY = renderTexture.texture.height - (characterY + cameraHeight / scale);


		// Clamp the camera to ensure it stays within the map bounds
		if (cameraX < 0) cameraX = 0;
		if (cameraX + scaledWidth > renderTexture.texture.width)
			cameraX = renderTexture.texture.width - scaledWidth;
		if (cameraY < 0) cameraY = 0;
		if (cameraY + scaledHeight > renderTexture.texture.height)
			cameraY = renderTexture.texture.height - scaledHeight;
		/*std::cout << "Camera: (" << cameraX << ", " << cameraY << "), Scale: " << scale << std::endl;
		std::cout << "Character: (" << characterX << ", " << characterY << ")" << std::endl;*/
	}





	void render() const {
		Rectangle sourceRec = {
			cameraX,
			cameraY,
			cameraWidth / scale,
			-cameraHeight / scale // Negative height to flip vertically
		};

		Rectangle destRec = {
			0, 0,                        // Render starting at the screen's top-left
			(float)GetScreenWidth(),     // Scale to fit the screen width
			(float)GetScreenHeight()     // Scale to fit the screen height
		};

		DrawTexturePro(renderTexture.texture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
	}


	void beginDrawing() {
		BeginTextureMode(renderTexture);
		ClearBackground(RAYWHITE);
	}

	void endDrawing() {
		EndTextureMode();
	}

	void setScale(float newScale) {
		scale = newScale;
		if (scale < 0.1f) scale = 0.1f; // Prevent too small scale
	}
};

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
	bool isJumping;
	bool horizontalOrientation = true; //true = right, false = left

	InputManager& inputManager; // Thêm đối tượng InputManager

public:
	Object(Vector2 position, Vector2 size, Texture& texture, InputManager& inputMgr)
		: position(position), size(size), texture(texture), inputManager(inputMgr) {
		velocity = Vector2(0, 0);
		maxSpeed = Vector2(1000, 600);
		acceleration = Vector2(1000, 500);
		isJumping = false;

		inputManager.addListener(*this);  // Đăng ký Object làm listener
		cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
		this->size = cur->getSize();
		this->position.y = 512.f - this->size.y;
		cur->reset();
	}

	~Object() {
		inputManager.removeListener(*this);  // Xóa listener khi Object bị hủy
	}

	void onKey(KeyboardKey key, bool pressed) override {
		//Xử lí các nút bấm có tính năng đặc biệt (bắn lửa, )
	}

	void update(float deltaTime) {
		// Gia tốc hãm
		const float deceleration = 2000.0f; // Gia tốc hãm (pixel/s^2)
		cur->update(deltaTime);
		// Di chuyển theo trục X
		if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {  // Nhấn D (phải) nhưng không nhấn A (trái)
			if (velocity.x < 0) {  // Đang di chuyển sang trái, hãm lại
				if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
				velocity.x += deceleration * deltaTime;
				if (velocity.x > 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
			}
			else {
				velocity.x += acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi phải
				if (isJumping == false) {
					cur = RESOURCE_MANAGER.getAnimation("superluigi_walk_right");
					this->size = cur->getSize();
					if (velocity.x >= maxSpeed.x) {
						cur = RESOURCE_MANAGER.getAnimation("superluigi_run_right");
						this->size = cur->getSize();
					}
				}
			}
		}
		else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {  // Nhấn A (trái) nhưng không nhấn D (phải)
			if (velocity.x > 0) {  // Đang di chuyển sang phải, hãm lại
				if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
				velocity.x -= deceleration * deltaTime;
				if (velocity.x < 0) velocity.x = 0; // Dừng hoàn toàn trước khi đổi hướng
			}
			else {
				velocity.x -= acceleration.x * deltaTime; // Tiếp tục tăng tốc khi đi trái
				if (isJumping == false) {
					cur = RESOURCE_MANAGER.getAnimation("superluigi_walk_left");
					this->size = cur->getSize();
					if (abs(velocity.x) >= maxSpeed.x) {
						cur = RESOURCE_MANAGER.getAnimation("superluigi_run_left");
						this->size = cur->getSize();
					}
				}
			}

		}
		else { // Không nhấn phím di chuyển nào
			if (velocity.x > 0) {
				velocity.x -= deceleration * deltaTime;
				if (velocity.x < 0) velocity.x = 0;
				if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
			}
			else if (velocity.x < 0) {
				velocity.x += deceleration * deltaTime;
				if (velocity.x > 0) velocity.x = 0;
				if (isJumping == false) cur = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
			}
		}

		if (velocity.x > 0) horizontalOrientation = true;
		else if (velocity.x < 0) horizontalOrientation = false;

		// Kiểm tra nhảy khi nhấn phím SPACE và đang không nhảy
		if (IsKeyDown(KEY_SPACE) && !isJumping) {
			velocity.y = -jumpForce;  // Đẩy lên
			isJumping = true;  // Đánh dấu là đang nhảy
			PlaySound(*RESOURCE_MANAGER.getSound("jump.wav"));
		}

		// Gia tốc trọng trường
		else if (isJumping) {
			velocity.y += gravity * deltaTime; // Gia tốc trọng trường tác động
			// Kiểm tra đối tượng đã chạm mặt đất chưa
			if (onGround()) {
				position.y = 512.f - size.y;  // Giới hạn trên mặt đất
				velocity.y = 0;  // Dừng chuyển động dọc trục Y
				isJumping = false;  // Không còn nhảy nữa
			}
		}

		// Giới hạn vận tốc (max speed)
		if (fabs(velocity.x) > maxSpeed.x) {
			velocity.x = (velocity.x > 0) ? maxSpeed.x : -maxSpeed.x;
		}

		if (isJumping) {
			if (horizontalOrientation) cur = RESOURCE_MANAGER.getAnimation("superluigi_jump_right");
			else cur = RESOURCE_MANAGER.getAnimation("superluigi_jump_left");
			this->size = cur->getSize();
		}

		if (isIdle() && !isJumping) {
			if (horizontalOrientation) cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
			else cur = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
			this->size = cur->getSize();
		}

		// Cập nhật vị trí mới
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;

		this->size = cur->getSize();
	}

	void draw() const {
		//Rectangle destRect = { position.x, position.y, size.x, size.y };
		//Rectangle srcRect = { 0, 0, (isFlipped ? -texture.width : texture.width), texture.height };
		//DrawTexturePro(texture, srcRect, destRect, { 0, 0 }, 0.f, WHITE); // Vẽ texture
		cur->render(position);
	}

	const Rectangle getRectangle() const {
		return { position.x, position.y, size.x, size.y };
	}

	bool onGround() const {
		if (position.y + size.y >= 512.f) return true;
		return false;
	}

	bool isIdle() const {
		return (velocity.x == 0.f && velocity.y == 0.f);
	}
};
class Chunk {
private:
	vector<Entity*> blocks;
	vector<Entity*> enemies;
	vector<Entity*> items;
public:
	int x; //coord                   
	bool isLoaded;             // Whether this chunk is loaded

	Chunk(int x) : x(x), isLoaded(false) {}

	void load() {
		isLoaded = true;
	}

	void unload() {
		isLoaded = false;
		//blocks.clear();
	}
	void clear()
	{
		blocks.clear();
	}

	void render() const {
		if (isLoaded) {
			for (const Entity* entity : blocks,enemies,items)
				entity->draw();
		}
	}
	void update()
	{
		// enemy ai

		// character update

		// handle collision
		CollisionInterface IColl;
		for (Entity* enemy : enemies)
		{
			for (Entity* block : blocks)
				IColl.resolve(*enemy, *block);
			//
		}


		//animation update
	}
};
class GameEngine {
private:
	Map* map;
	Object* testObject;
	//vector<Chunk> chunks; 

	//int chunkSize;        // Size of each chunk in pixels
	GameCamera camera;
	//float characterX;
	//int CenterChunk; /// later

public:
	//GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, int chunkSize)
	//	: /*map(mapWidth, mapHeight)*/
	//	camera(screenWidth, screenHeight, mapWidth, screenHeight), chunkSize(chunkSize),
	//	characterX(500) {
	//	//CenterChunk = (int)(characterX / chunkSize);
	//	int numChunks = int(mapWidth / chunkSize);
	//	//chunks.reserve(numChunks);
	//	//for (int i = 0; i < numChunks; ++i) {
	//	//	chunks.emplace_back(i);
	//	//}
	//}
	GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, Map& map,Object& object)
		: camera(screenWidth, screenHeight, mapWidth, screenHeight,1.25), map(&map),testObject(&object) {};
	// implement later
   /* void loadMap(const string& filePath) {
		map.loadFromFile(filePath);

		// Assign blocks to chunks
		for (auto& block : map.getBlocks()) {
			int blockChunk = block.getPos().first / chunkSize;
			if (blockChunk >= 0 && blockChunk < chunks.size()) {
				chunks[blockChunk].blocks.push_back(&block);
			}
		}
	}*/
	~GameEngine()
	{
		map = nullptr;
		testObject = NULL;
	}
	void resolveCollision() {};

	void update() {
		// 
		// follow character
		float deltaTime = GetFrameTime();
		//inputManager.update();
		testObject->update(deltaTime);
		//int currentChunk = (int)(characterX / chunkSize); // get current chunk
		//updateChunks(currentChunk);
		//for (int i = 0; i < chunks.size(); ++i)
		//{
		//	chunks[i].update();
		//}
		//camera.update(characterX, 0);
		camera.update(testObject->getRectangle().x, testObject->getRectangle().y);
	}

	//void updateChunks(int characterChunk) {
	//	// Load and keep chunks within range
	//	for (int i = characterChunk - 1; i <= characterChunk + 1; ++i) {
	//		if (i >= 0 && i < chunks.size() && !chunks[i].isLoaded) {
	//			chunks[i].load();
	//		}
	//	}

	//	// Unload chunks outside the range
	//	for (int i = 0; i < chunks.size(); ++i) {
	//		if (chunks[i].isLoaded && (i < characterChunk - 1 || i > characterChunk + 1)) {
	//			chunks[i].unload();
	//		}
	//	}
	//}

	void render() {
		camera.beginDrawing();
		map->renderBackground();
		map->renderAllBlock();
		// Render active chunks
		//for (const auto& chunk : chunks) {
		//	chunk.render();
		//}
		testObject->draw();
		// Render character
		//DrawRectangle((int)characterX - 10, 500 - 10, 20, 20, RED);

		camera.endDrawing();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		camera.render();
		EndDrawing();
	}

	void run() {

		while (!WindowShouldClose()) {
			if (FPS_MANAGER.update()) {
				// Update music stream
				UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));
				update();
				render();


			}
		}
	}
};


