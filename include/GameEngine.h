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
	vector<Entity*> fireball;
	vector<Entity*> effects;
	vector<Entity*> decor;
	vector<Entity*> testEntities;
	int score;
	GameCamera camera;
	bool isPaused;

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
		decor = map.getDecor();
		score = 0;
		isPaused = false;
	};
	~GameEngine()
	{
		player = NULL;
		blocks.clear();
		blocks.clear();
		blocks.clear();
	}
	void resolveCollision() {};

	void addFireBall(Entity* fireball) {
		this->fireball.push_back(fireball);
	}

	void update() {
		if (IsKeyPressed(KEY_ENTER)) {
			isPaused = !isPaused;
		}
		if (isPaused)
		{
			return;
		}
		float deltaTime = GetFrameTime();
		//inputManager.update();
		player->update(deltaTime);
		for (Entity* i : (blocks)) {
			i->update(deltaTime);
		}
		for (Entity* i : (enemies)) {
			Plant* enemy = dynamic_cast<Plant*>(i);
			if (enemy) {
				enemy->setPlayerForFireball(player);
			}
			i->update(deltaTime);
		}
		for (size_t i = 0; i < fireball.size(); i++) {
			if (fireball[i]->isDead()) {
				delete fireball[i];
				fireball.erase(fireball.begin() + i);
				i--;
			}
			else {
				fireball[i]->update(deltaTime);
			}
			
		}

		//I think we have to update all entities before resolving collision
		//because the collision resolution may depend on the updated position of the entities
		handleCollision();
		camera.update(player->getX(), player->getY());
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
		for (Entity* enemy : enemies)
		{
			for (Entity* block : blocks)
			{
				IColl.resolve(*enemy, *block);
			}
		}
		player->setJumping(!isGrounded);
	}

	void render() {
		camera.beginDrawing();
		map.renderBackground();
		for (Entity* i : blocks)
		{
			i->draw();
			//DrawRectangleRec(i->getRectangle(), ORANGE);
		}
		if (!isPaused)
		{
			for (Entity* i : enemies)
			{
				i->draw();
				//DrawRectangleRec(i->getRectangle(), ORANGE);
			}
		for (Entity* i : fireball) {
			i->draw();

		}
		for (Entity* i : items)
		{
			i->draw();
		}
		player->draw();
		}
		//DrawRectangleRec(player->getRectangle(), ORANGE);
		for (Entity* i : decor)
			i->draw();
		camera.endDrawing();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		camera.render();


		//////
		char buffer[10];
		sprintf_s(buffer, "%d", score);
		DrawText("Score: ", 10, 10, 40, BLACK);
		DrawText(buffer, 180, 10, 40, BLACK);
		if (isPaused) {
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
			DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
		}

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


