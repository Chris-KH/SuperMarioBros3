#include <iostream>
#include <vector>
#include <raylib.h>
#include"../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Collision.h"
#include "../include/Shell.h"
#include "../include/Plant.h"
#include "../include/Mushroom.h"
#include "../include/Flower.h"
#include "../include/GUI.h"
#include "../include/Effect.h"
#include"../include/Character.h"

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
    items = map.getItems();
    decor = map.getDecor();
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
}

GameEngine::~GameEngine() {
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
    for (size_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }
    for (size_t i = 0; i < fireball.size(); ++i) {
        delete fireball[i];
    }

    player = nullptr;
    blocks.clear();
    enemies.clear();
    items.clear();
    shells.clear();
    effects.clear();
    fireball.clear();
}

void GameEngine::resolveCollision() {}

void GameEngine::addScore(int amount) {
    player->setScores(player->getScores() + amount);
}

void GameEngine::addFireBall(Fireball* fireball) {
    this->fireball.push_back(fireball);
}

void GameEngine::addEnemy(Enemy* enemy) {
    this->enemies.push_back(enemy);
}

void GameEngine::addEffect(Effect* effect) {
    this->effects.push_back(effect);
}

void GameEngine::addShell(Shell* shell) {
    this->enemies.push_back(shell);
    this->shells.push_back(shell);
}

void GameEngine::addItem(Item* item) {
    this->items.push_back(item);
}

void GameEngine::update(float deltaTime) {
    if (IsKeyPressed(KEY_ENTER)) {
        isPaused = !isPaused;
        if (died)
        {
            died = false;
            player->setLostLife(false);
            player->resetInGame();
            resetGame();
            resetTimer();
        }
        else if (isPaused) {
            RESOURCE_MANAGER.playSound("pause.wav");
        }
    }
    if (isPaused || cleared) {
        return;
    }
    this->time -= deltaTime;
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i]->isDead()) {
            delete blocks[i];
            blocks.erase(blocks.begin() + i);
            i--;
        }
        else {
            blocks[i]->update(deltaTime);
        }
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        Plant* enemy = dynamic_cast<Plant*>(enemies[i]);
        if (enemy) {
            enemy->setPlayerForFireball(player);
        }
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->isDead()) {
            if (enemies[i]->getEnemyType() == SHELL) {
                auto it = find(shells.begin(), shells.end(), enemies[i]);
                if (it != shells.end()) {
                    if (enemies[i] == player->getHoldShell()) {
                        player->setHoldingShell(nullptr);
                        player->setHolding(false);
                    }
                    shells.erase(it);
                }
            }
            delete enemies[i];
            enemies[i] = nullptr;
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

    for (size_t j = 0; j < blocks.size(); j++) {
        if (IColl.resolve(player, blocks[j])) isGrounded = true;
        for (size_t i = 0; i < enemies.size(); i++) IColl.resolve(enemies[i], blocks[j]);
        for (size_t i = 0; i < items.size(); i++) IColl.resolve(items[i], blocks[j]);
        for (size_t i = 0; i < fireball.size(); i++) {
            if (fireball[i]->getFireballType() == CHARACTER_FIREBALL) IColl.resolve(fireball[i], blocks[j]);
        }
    }

    player->setJumping(!isGrounded);

    for (size_t i = 0; i < shells.size(); i++) {
        if (shells[i]->getIsHold() == false && shells[i]->getIsKicked() == false) continue;
        for (size_t j = 0; j < enemies.size(); j++) {
            if (shells[i] == enemies[j]) continue;
            IColl.resolve(shells[i], enemies[j]);
        }
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getEnemyType() == SHELL && player->getHoldShell() == enemies[i]) continue;

        for (Fireball* ball : fireball) {
            if (ball->getFireballType() == CHARACTER_FIREBALL) IColl.resolve(ball, enemies[i]);
        }
        IColl.resolve(player, enemies[i]);
    }
       
    for (size_t i = 0; i < fireball.size(); i++) {
        if (fireball[i]->getFireballType() == ENEMY_FIREBALL) {
            IColl.resolve(fireball[i], player);
        }
    }

    for (size_t i = 0; i < items.size(); i++) {
        IColl.resolve(player, items[i]);
    }
}

void GameEngine::render(float deltaTime) {
    camera.beginDrawing();
    map.renderBackground();

    bool lostLife = player->isLostLife();

    for (size_t i = 0; i < blocks.size(); ++i) {
        blocks[i]->draw(deltaTime);
        //DrawRectangleRec(blocks[i]->getRectangle(), BLACK);
    }
        
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (player->getHoldShell() != nullptr) {
            if (dynamic_cast<Shell*>(enemies[i]) == player->getHoldShell()) continue;
        }
        if (isPaused || lostLife)
            enemies[i]->draw(0);
        else
            enemies[i]->draw(deltaTime);
    }

    for (size_t i = 0; i < items.size(); ++i) {
        if (isPaused || lostLife)
            items[i]->draw(0);
        else
            items[i]->draw(deltaTime);
    }

    for (size_t i = 0; i < fireball.size(); ++i) {
        if (isPaused || lostLife)
            fireball[i]->draw(0);
        else
            fireball[i]->draw(deltaTime);
    }

    if (isPaused)
        player->draw(0);
    else
        player->draw(deltaTime);

    for (size_t i = 0; i < effects.size(); ++i) {
        if (isPaused || lostLife)
            effects[i]->draw(0);
        else
            effects[i]->draw(deltaTime);
    }

    for (Entity* i : decor)
        i->draw();
    camera.endDrawing();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    camera.render();

    if (lostLife == false) GUI::drawStatusBar(player);

    if (isPaused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
        if (cleared) {
            GUI::drawLevelClear();
        }
        else if (gameover)
            GUI::drawGameOverScreen();
        else if (died)
            GUI::drawDeathScreen();
        else
            GUI::drawPauseMenu();
    }

    EndDrawing();
}

bool GameEngine::run() {
    bool flag = true;

    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    // Load and play the new music
    while (!WindowShouldClose()) {
        if (FPS_MANAGER.update()) {
            float deltaTime = GetFrameTime();
            this->deltaTime = deltaTime;
            if (SETTINGS.isMusicEnabled()&&!isPaused)
                UpdateMusicStream(*RESOURCE_MANAGER.getMusic(level->getMusic()));

            update(deltaTime);
            render(deltaTime);
        }

        if (cleared == true && isPaused == false) {
            RESOURCE_MANAGER.stopCurrentMusic();
            RESOURCE_MANAGER.playMusic("Overworld.mp3");
            return true;
        }

        if (gameover == true && isPaused == false) break;

        if (this->time <= 0) player->setLostLife(true);
        if (player->getY() > getBound().y && player->getPhase() != Character::CLEARLEVEL_PHASE) player->setLostLife(true);

        if (player->getX() >= map.getMapSize().x && RESOURCE_MANAGER.isSoundPlaying("level_clear.wav") == false) {
            cleared = true;
            isPaused = true;
            player->setVelocity({ 0.f, 0.f });
        }   
        else if (player->getX() >= map.getMapSize().x - 150.f) {
            if (player->getPhase() != Character::CLEARLEVEL_PHASE) {
                RESOURCE_MANAGER.stopCurrentMusic();
                RESOURCE_MANAGER.playSound("level_clear.wav");
                player->setPhase(Character::CLEARLEVEL_PHASE);
            }
        }
        else if (player->isLostLife() && player->getBottom() < 0.f) {
            if (player->getLives() < 0) {
                gameover = true;
                isPaused = true;
            }
            else {
                died = true;
                isPaused = true;
            }
        }
        else if (player->isLostLife()) {
            if (player->getPhase() != Character::DEAD_PHASE) {
                RESOURCE_MANAGER.stopCurrentMusic();
                player->setPhase(Character::DEAD_PHASE);
                if (player->getLives() < 0) {
                    RESOURCE_MANAGER.playSound("game_over.wav");
                }
                else {
                    RESOURCE_MANAGER.playSound("lost_life.wav");
                }
            }
        }

        
    }
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic("Overworld.mp3");
    return false;
}

string GameEngine::getCurrentMapName()
{
    return level->getName();
}

float GameEngine::getGlobalTime()
{
    return deltaTime;
}

float GameEngine::resetTimer()
{
    this->time = 300;
    return 300.f;
}

bool GameEngine::isOver()
{
    return gameover;
}

void GameEngine::resetGame()
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
    for (size_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }
    for (size_t i = 0; i < fireball.size(); ++i) {
        delete fireball[i];
    }
    blocks.clear();
    enemies.clear();
    items.clear();
    shells.clear();
    effects.clear();
    fireball.clear();
    map.clearThings();
    
    RESOURCE_MANAGER.playMusic(level->getMusic());
    map.loadFromFile(level->getMapPath());
    map.loadBackground(level->getBackGroundPath());
    blocks = map.getBlocks();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
}

float GameEngine::getRemainingTime()
{
    return this->time;
}
Vector2 GameEngine::getBound()
{
    return map.getMapSize();
}
