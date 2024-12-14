#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Collision.h"
#include "Character.h"
class GameCamera {
public:
	float cameraX;
	float cameraY;
	float cameraWidth;
	float cameraHeight;
	float scale; // Scaling factor

	RenderTexture2D renderTexture;

	GameCamera(float width, float height, int mapWidth, int mapHeight, float initialScale = 1.0f);
	~GameCamera();

	void update(float characterX, float characterY);
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
};
//class Chunk {
//private:
//	vector<Entity*> blocks;
//	vector<Entity*> enemies;
//	vector<Entity*> items;
//public:
//	int x; //coord                   
//	bool isLoaded;             // Whether this chunk is loaded
//
//	Chunk(int x) : x(x), isLoaded(false) {}
//
//	void load() {
//		isLoaded = true;
//	}
//
//	void unload() {
//		isLoaded = false;
//		//blocks.clear();
//	}
//	void clear()
//	{
//		blocks.clear();
//	}
//
//	void render() const {
//		if (isLoaded) {
//			for (const Entity* entity : blocks,enemies,items)
//				entity->draw();
//		}
//	}
//	void update()
//	{
//		// enemy ai
//
//		// character update
//
//		// handle collision
//		CollisionInterface IColl;
//		for (Entity* enemy : enemies)
//		{
//			for (Entity* block : blocks)
//				IColl.resolve(*enemy, *block);
//			//
//		}
//
//
//		//animation update
//	}
//};
class GameEngine {
private:
	Map* map;
	Character* player;
	vector<Entity*>* blocks; 
	//int chunkSize;
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
	GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, Map& map,Character*& player)
		: camera(screenWidth, screenHeight, mapWidth, screenHeight, 1), map(&map), player(player) {
		blocks = map.returnBlockArray();
	};
	~GameEngine()
	{
		map = nullptr;
		player = NULL;
	}
	void resolveCollision() {};

	void update() {
		float deltaTime = GetFrameTime();
		//inputManager.update();
		handleCollision();
		player->update(deltaTime);

		//int currentChunk = (int)(characterX / chunkSize); // get current chunk
		//updateChunks(currentChunk);
		//for (int i = 0; i < chunks.size(); ++i)
		//{
		//	chunks[i].update();
		//}
		//camera.update(characterX, 0);
		camera.update(player->getX(), player->getY());
	}
	void handleCollision()
	{
		CollisionInterface IColl;
		for (Entity* block : *(blocks))
		{
			IColl.resolve(*player, *block);
		}
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
		player->draw();
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


