#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Collision.h"
#include "Character.h"
class CollisionInterface;
class GameCamera {
public:
	float cameraX;
	float cameraY;
	float cameraWidth;
	float cameraHeight;
	float scale; // Scaling factor

	RenderTexture2D renderTexture;

	GameCamera(float width, float height, float mapWidth, float mapHeight, float initialScale = 1.0f);
	~GameCamera();

	void update(float characterX, float characterY);
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
};

class GameEngine {
private:
	Map* map;
	Character* player;
	vector<Entity*>* blocks;
	vector<Entity*> testEntities;
	int score;
	GameCamera camera;
	//float characterX;
	//int CenterChunk; /// later

public:

	GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, Map& map, Character*& player)
		: camera(screenWidth, screenHeight, mapWidth, screenHeight, 1.75f), map(&map), player(player) {
		blocks = map.returnBlockArray(); score = 0;
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
		player->update(deltaTime);
		handleCollision();
		for (Entity* i : *(blocks))
		{
			i->update(deltaTime);
		}
		//int currentChunk = (int)(characterX / chunkSize); // get current chunk
		//updateChunks(currentChunk);
		//for (int i = 0; i < chunks.size(); ++i)
		//{
		//	chunks[i].update();
		//}
		//camera.update(characterX, 0);
		camera.update(player->getX(), player->getY());
		//cout << deltaTime << endl;
	}
	void handleCollision()
	{
		CollisionInterface IColl;
		//player->setJumping(true);
		bool isGrounded = false;
		for (Entity* block : *(blocks))
		{
			if (IColl.resolve(*player, *block))
			{
				isGrounded = true;
				//player->setJumping(false);
				//break;
			}
		}
		for (Entity* things : testEntities)
		{
			if (IColl.resolve(*player, *things))
			{
				isGrounded = true;
			}
		}
		player->setJumping(!isGrounded);
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
		for (Entity* i : testEntities)
		{
			i->draw();
		}
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
		char buffer[10];
		sprintf_s(buffer, "%d", score);
		DrawText("Score: ", 10, 10, 40, BLACK);
		DrawText(buffer, 180, 10, 40, BLACK);
		EndDrawing();
	}

	void run() {

		/*MovingBlock testBlock(Vector2(850, 300), Vector2(100, 32), BLACK);
		testBlock.setBounds(850, 1000, 300, 500);
		testBlock.setVelocity(Vector2(50, 50));
		MovingBlock* blo = &testBlock;
		testEntities.push_back(blo);*/
		while (!WindowShouldClose()) {
			if (FPS_MANAGER.update()) {
				//cout << FPS_MANAGER.getFrameRate() << '\n';
				// Update music stream
				if(SETTINGS.isMusicEnabled())
					UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));
				update();
				render();

				//cout << GetFrameTime() << endl;
			}
		}
	}
};


