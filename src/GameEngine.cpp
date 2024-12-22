#include <iostream>
#include <vector>
#include <raylib.h>
#include"../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Collision.h"
#include "../include/Shell.h"
#include "../include/Plant.h"
#include "../include/Mushroom.h"
#include "../include/GUI.h"

using namespace std;

GameEngine* globalGameEngine = nullptr;

GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player)
    : camera(screenWidth, screenHeight, 1.75f), level(&level), player(player) {
    map.loadFromFile(level.getMapPath());
    map.loadBackground(level.getBackGroundPath());
    Vector2 Msize = map.getMapSize();
    camera.loadRenderTexture(Msize);
    blocks = map.getBlocks();
    enemies = map.getEnemies();
    decor = map.getDecor();
    isPaused = false;
    deltaTime = 0.f;
}

GameEngine::~GameEngine() {
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
    player = nullptr;
    blocks.clear();
    enemies.clear();
    items.clear();
    shells.clear();
    effects.clear();
}

void GameEngine::resolveCollision() {}

void GameEngine::addScore(int amount) {
    player->setScores(player->getScores() + amount);
}

void GameEngine::addFireBall(Fireball* fireball) {
    this->fireball.push_back(fireball);
}

void GameEngine::addEnemy(Entity* enemy) {
    this->enemies.push_back(enemy);
}

void GameEngine::addEffect(Entity* effect) {
    this->effects.push_back(effect);
}

void GameEngine::addShell(Entity* shell) {
    this->enemies.push_back(shell);
    this->shells.push_back(shell);
}

void GameEngine::addItem(Entity* item) {
    this->items.push_back(item);
}

void GameEngine::update(float deltaTime) {
    if (IsKeyPressed(KEY_ENTER)) {
        isPaused = !isPaused;
    }
    if (isPaused) {
        return;
    }

    for (Entity* i : blocks) {
        i->update(deltaTime);
    }
    for (Entity* i : enemies) {
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

    handleCollision();
    camera.update(player->getX(), player->getY());
}

void GameEngine::handleCollision() {
    CollisionInterface IColl;
    bool isGrounded = false;

    for (Entity* block : blocks) {
        if (IColl.resolve(player, block)) isGrounded = true;
        for (Entity* enemy : enemies)IColl.resolve(enemy, block);
        for (Entity* item : items)IColl.resolve(item, block);
        for (Fireball* ball : fireball) {
            if (ball->getFireballType() == CHARACTER_FIREBALL) IColl.resolve(ball, block);
        }
    }

    player->setJumping(!isGrounded);

    for (Entity* enemy : enemies) {
        for (Fireball* ball : fireball) {
            if (ball->getFireballType() == CHARACTER_FIREBALL) IColl.resolve(ball, enemy);
        }
        IColl.resolve(player, enemy);
    }
       
    for (Fireball* ball : fireball) {
        if (ball->getFireballType() == ENEMY_FIREBALL) {
            IColl.resolve(ball, player);
        }
    }

    for (Entity* item : items) IColl.resolve(player, item);
}

void GameEngine::render(float deltaTime) {
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
    for (Entity* i : items) {
        if (isPaused)
            i->draw(0);
        else
            i->draw(deltaTime);
    }

    player->draw(deltaTime);

    for (Entity* i : effects) {
        if (isPaused)
            i->draw(0);
        else
            i->draw(deltaTime);
    }

    for (Entity* i : decor)
        i->draw();
    camera.endDrawing();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    camera.render();

    GUI::drawStatusBar(player);

    //DrawRectangle(0, 0, GetScreenWidth(), 60, DARKGRAY); // Background bar for the stats

    //DrawText("LIVES: ", 10, 10, 40, WHITE);
    //DrawText(to_string(player->getLives()).c_str(), 160, 10, 40, WHITE);

    //DrawRectangle(300, 10, 30, 40, YELLOW);
    //DrawRectangle(310, 20, 10, 20, ORANGE);
    //DrawText("x", 340, 10, 40, WHITE);
    //DrawText(to_string(player->getCoins()).c_str(), 370, 10, 40, WHITE);

    //DrawText("Score: ", 500, 10, 40, WHITE);
    //DrawText(to_string(player->getScores()).c_str(), 650, 10, 40, WHITE);

    //Texture2D texture = LoadTexture("../assets/Background/heart.png");
    //DrawTexture(texture, 0, 0, WHITE);

    if (isPaused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
        DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
    }

    EndDrawing();
}

bool GameEngine::run() {
    Item* testItem = new Mushroom(MUSHROOM_1UP, { 300, 450 });
    items.push_back(testItem);
    while (!WindowShouldClose()) {
        if (FPS_MANAGER.update()) {
            float deltaTime = GetFrameTime();
            this->deltaTime = deltaTime;
            if (SETTINGS.isMusicEnabled())
                UpdateMusicStream(*RESOURCE_MANAGER.getMusic("Overworld.mp3"));

            update(deltaTime);
            render(deltaTime);
        }

        if (player->getX() >= map.getMapSize().x) {
            return true; // finished the level
        }
    }
    return false;
}

float GameEngine::getGlobalTime()
{
    return deltaTime;
}
