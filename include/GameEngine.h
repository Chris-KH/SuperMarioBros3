#ifndef ENGINE_H
#define ENGINE_H
#include "Camera.h"  // For the camera
#include "Character.h"   // For the player character
#include "Fireball.h"    // For fireball handling
#include "Map.h"
#include <vector>

class Effect;
class Enemy;

class GameEngine {
private:
    Level* level;      
    Map map;           
    Character* player; 
    std::vector<BaseBlock*> blocks;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::vector<Fireball*> fireball;
    std::vector<Effect*> effects;
    std::vector<BaseBlock*> decor;
    std::vector<Shell*> shells;
    std::vector<Entity*> testEntities;
    GameCamera camera;  
    bool isPaused;
    bool cleared = false;
    bool died = false;
    bool gameover = false;
    float time;
    float deltaTime;

public:
    GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player);
    ~GameEngine();
    void resolveCollision();
    void addScore(int amount);
    void addFireBall(Fireball* fireball);
    void addEnemy(Enemy* enemy);
    void addEffect(Effect* effect);
    void addShell(Shell* shell);
    void addItem(Item* item);
    void update(float deltaTime);
    void handleCollision();
    void render(float deltaTime);
    bool run();
    float getGlobalTime();
    float getRemainingTime();
    float resetTimer();
    bool isOver();
    void resetGame();
    Vector2 getBound();
};
extern GameEngine* globalGameEngine;
#endif