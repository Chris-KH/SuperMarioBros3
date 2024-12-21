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
		DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY); // Background bar for the stats

		// Display Lives
		DrawText("LIVES: ", 10, 10, 40, WHITE);
		char livesBuffer[3];
		sprintf_s(livesBuffer, "%d", player->getLives());
		DrawText(livesBuffer, 160, 10, 40, WHITE);

		// Display Coins
		DrawRectangle(300, 10, 30, 40, YELLOW);
		DrawRectangle(310, 20, 10, 20, ORANGE);
		char coinsBuffer[10];
		sprintf_s(coinsBuffer, "%d", player->getCoins());
		DrawText("x", 340, 10, 40, WHITE);
		DrawText(coinsBuffer, 370, 10, 40, WHITE);

		// Display Score
		DrawText("Score: ", 500, 10, 40, WHITE);
		char scoreBuffer[30];
		sprintf_s(scoreBuffer, "%d", player->getScores());
		DrawText(scoreBuffer, 650, 10, 40, WHITE);

		if (isPaused) {
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
			DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
		}

		/////////
		EndDrawing();
	}

	bool run() {

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
			if(player->getX() >= map.getMapSize().x)
				return true;
		}
		return false;
	}
};
extern GameEngine* globalGameEngine;


