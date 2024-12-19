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

	GameCamera(float width, float height, float initialScale = 1.0f);
	~GameCamera();
	void loadRenderTexture(Vector2 size);
	void update(float characterX, float characterY);
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
};

class GameEngine {
private:
	Level* level;
	Map map;
	Character* player;
	vector<Entity*> blocks;
	vector<Entity*> enemies;
	vector<Entity*> items;
	vector<Entity*> testEntities;
	int score;
	GameCamera camera;

public:

	GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player)
		: camera(screenWidth, screenHeight, 1.75f), level(&level), player(player)
	{
		map.loadFromFile(level.getMapPath());
		map.loadBackground(level.getBackGroundPath());
		Vector2 Msize = map.getMapSize();
		camera.loadRenderTexture(Msize);
		blocks = map.getBlocks();
		enemies = map.getEnemies();
		score = 0;
	};
	~GameEngine()
	{
		player = NULL;
		blocks.clear();
		blocks.clear();
		blocks.clear();
	}
	void resolveCollision() {};

	void update() {
		float deltaTime = GetFrameTime();
		//inputManager.update();
		player->update(deltaTime);
		handleCollision();
		for (Entity* i : (blocks))
		{
			i->update(deltaTime);
		}
		for (Entity* i : (enemies))
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
		for (Entity* block : (blocks))
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
		map.renderBackground();
		for (Entity* i : blocks)
		{
			i->draw();
		}
		for (Entity* i : enemies)
		{
			i->draw();
		}
		for (Entity* i : items)
		{
			i->draw();
		}
		player->draw();

		camera.endDrawing();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		camera.render();


		//////
		char buffer[10];
		sprintf_s(buffer, "%d", score);
		DrawText("Score: ", 10, 10, 40, BLACK);
		DrawText(buffer, 180, 10, 40, BLACK);
		/////////
		EndDrawing();
	}

	void run() {

		while (!WindowShouldClose()) {
			if (FPS_MANAGER.update()) {
				//cout << FPS_MANAGER.getFrameRate() << '\n';
				// Update music stream
				if(SETTINGS.isMusicEnabled())
					UpdateMusicStream(*RESOURCE_MANAGER.getMusic("Overworld.mp3"));				
				update();
				render();

				//cout << GetFrameTime() << endl;
			}
		}
	}
};
extern GameEngine* globalGameEngine;


