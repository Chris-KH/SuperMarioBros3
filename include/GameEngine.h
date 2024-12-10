#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Entity.h"
#include "Block.h"
#include "Collision.h"

class GameCamera {
public:
	float cameraX;          // GameCamera position on the X-axis
	float cameraY;          // GameCamera position on the Y-axis
	float cameraWidth;      // Width of the camera view
	float cameraHeight;     // Height of the camera view

	RenderTexture2D renderTexture; // Off-screen render texture

	GameCamera(float width, float height, int mapWidth, int mapHeight)
		: cameraWidth(width), cameraHeight(height), cameraX(0), cameraY(0) {
		renderTexture = LoadRenderTexture(mapWidth, mapHeight);
	}

	~GameCamera() {
		UnloadRenderTexture(renderTexture);
	}

	void update(float characterX, float characterY) {
		// Calculate the offset needed to center the camera on the character
		cameraX = characterX - cameraWidth / 2;
		cameraY = characterY - cameraHeight / 2;

		// Clamp the camera position so it doesn't go out of map bounds
		if (cameraX < 0) cameraX = 0;
		if (cameraY < 0) cameraY = 0;
		if (cameraX + cameraWidth > renderTexture.texture.width)
			cameraX = renderTexture.texture.width - cameraWidth;
		if (cameraY + cameraHeight > renderTexture.texture.height)
			cameraY = renderTexture.texture.height - cameraHeight;


	}
	void render() const {
		Rectangle sourceRec = { cameraX, cameraY, cameraWidth, cameraHeight };
		Rectangle destRec = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

		DrawTexturePro(renderTexture.texture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
	}

	// Begin drawing to the off-screen texture
	void beginDrawing() {
		BeginTextureMode(renderTexture);
		ClearBackground(RAYWHITE);
	}

	// End drawing to the off-screen texture
	void endDrawing() {
		EndTextureMode();
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
	Map map;
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
	GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, Map& map)
		: camera(screenWidth, screenHeight, mapWidth, screenHeight), map(map) {};
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

	void resolveCollision() {};

	void update() {
		// 
		// follow character

		//int currentChunk = (int)(characterX / chunkSize); // get current chunk
		//updateChunks(currentChunk);
		//for (int i = 0; i < chunks.size(); ++i)
		//{
		//	chunks[i].update();
		//}
		//camera.update(characterX, 0);
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
		map.renderBackground();
		map.renderAllBlock();
		// Render active chunks
		//for (const auto& chunk : chunks) {
		//	chunk.render();
		//}

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
			update();
			render();
		}
	}
};


