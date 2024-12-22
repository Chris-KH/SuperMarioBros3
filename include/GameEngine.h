#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Collision.h"
#include "Character.h"
#include "Mushroom.h"
#include "Star.h"
#include "Flower.h"
#include "Coin.h"
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
	vector<Fireball*> fireball;
	vector<Entity*> effects;
	vector<Entity*> decor;
	vector<Entity*> shells;
	vector<Entity*> testEntities;
	GameCamera camera;
	bool isPaused;
	float deltaTime;

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
		deltaTime = 0.f;
	};
	~GameEngine()
	{
		for (Entity* entity : blocks) {
			delete entity;
		}
		for (Entity* entity : enemies) {
			delete entity;
		}
		for (Entity* entity : items) {
			delete entity;
		}
		for (Entity* entity : decor) {
			delete entity;
		}
		for (Entity* entity : effects) {
			delete entity;
		}
		player = NULL;
		blocks.clear();
		enemies.clear();
		items.clear();
		shells.clear();
		effects.clear();
	}
	void resolveCollision() {};

	void addFireBall(Fireball* fireball) {
		this->fireball.push_back(fireball);
	}

	void addEnemy(Entity* enemy) {
		this->enemies.push_back(enemy);
	}

	void addEffect(Entity* effect) {
		this->effects.push_back(effect);
	}

	void addShell(Entity* shell)
	{
		this->enemies.push_back(shell);
		this->shells.push_back(shell);
	}
	void addItem(Entity* item) {
		this->items.push_back(item);
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
		this->deltaTime = deltaTime;
		//inputManager.update();
		for (Entity* i : (blocks)) {
			i->update(deltaTime);
		}
		for (Entity* i : (enemies)) {
			Plant* enemy = dynamic_cast<Plant*>(i);
			if (enemy) {
				enemy->setPlayerForFireball(player);
			}
		}
		for (size_t i = 0; i < enemies.size(); i++) {
			if (enemies[i]->isDead()) {
				auto it = find(shells.begin(), shells.end(), enemies[i]);
				if (it != shells.end())
					shells.erase(it);
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				i--;
			}
			else {
				enemies[i]->update(deltaTime);
			}

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
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i]->isDead()) {
				delete items[i];
				items.erase(items.begin() + i);
				i--;
			}
			else {
				items[i]->update(deltaTime);
			}
		}

		for (size_t i = 0; i < effects.size(); i++) {
			if (effects[i]->isDead()) {
				delete effects[i];
				effects.erase(effects.begin() + i);
				i--;
			}
			else {
				effects[i]->update(deltaTime);
			}
		}

		player->update(deltaTime);

		//I think we have to update all entities before resolving collision
		//because the collision resolution may depend on the updated position of the entities
		handleCollision();
		camera.update(player->getX(), player->getY());
	}
	void handleCollision()
	{
		CollisionInterface IColl;
		bool isGrounded = false;

		for (Entity* block : blocks) {
			if (IColl.resolve(player, block)) 
				isGrounded = true;
			for (Entity* enemy : enemies) 
				IColl.resolve(enemy, block);
			for (Entity* item : items) 
				IColl.resolve(item, block);
		}
		player->setJumping(!isGrounded);
		for (Entity* i : items)
			IColl.resolve(player,i);
		for (Entity* i : enemies)
		//	for (Entity* j : enemies)
		//		if (i != j)
		//			IColl.resolve(*i, *j);
			IColl.resolve(player, i);
		//for (Entity* i : )
	}

	void render() {
		camera.beginDrawing();
		map.renderBackground();
		for (Entity* i : blocks)
			i->draw(deltaTime);
		for (Entity* i : enemies) {
			if (player->getHoldShell() != nullptr) {
				if (dynamic_cast<Shell*>(i) == player->getHoldShell()) continue;
			}
			if (isPaused)
				i->draw(0);
			else
				i->draw(deltaTime);
		}
		for (Entity* i : fireball) {
			if (isPaused)
				i->draw(0);
			else
				i->draw(deltaTime);
		}
		for (Entity* i : items)
		{
			if (isPaused)
				i->draw(0);
			else
				i->draw(deltaTime);
		}

		for (Entity* i : effects) {
			if (isPaused)
				i->draw(0);
			else
				i->draw(deltaTime);
		}

		player->draw(deltaTime);

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
		DrawText(to_string(player->getLives()).c_str(), 160, 10, 40, WHITE);

		// Display Coins
		DrawRectangle(300, 10, 30, 40, YELLOW);
		DrawRectangle(310, 20, 10, 20, ORANGE);
		DrawText("x", 340, 10, 40, WHITE);
		DrawText(to_string(player->getCoins()).c_str(), 370, 10, 40, WHITE);

		// Display Score
		DrawText("Score: ", 500, 10, 40, WHITE);
		DrawText(to_string(player->getScores()).c_str(), 650, 10, 40, WHITE);

		if (isPaused) {
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
			DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
		}

		/////////
		EndDrawing();
	}

	bool run() {
		Item* testItem = new Star(YELLOW_STAR, { 300,450 });
		items.push_back(testItem);
		while (!WindowShouldClose()) {
			if (FPS_MANAGER.update()) {
				//cout << FPS_MANAGER.getFrameRate() << '\n';
				// Update music stream
				
				if(SETTINGS.isMusicEnabled())
					UpdateMusicStream(*RESOURCE_MANAGER.getMusic("Overworld.mp3"));

					update();
				
				render();

				//cout << player->getPosition().y << endl;
			}
			if(player->getX() >= map.getMapSize().x)
				return true;// finished the level
		}
		return false;
	}
};
extern GameEngine* globalGameEngine;


