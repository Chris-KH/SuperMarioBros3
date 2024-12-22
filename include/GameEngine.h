#ifndef ENGINE_H
#define ENGINE_H
#include "Camera.h"  // For the camera
#include "Character.h"   // For the player character
#include "Fireball.h"    // For fireball handling
#include "Map.h"
#include <vector>

class GameEngine {
private:
    Level* level;      
    Map map;           
    Character* player; 
    std::vector<Entity*> blocks;
    std::vector<Entity*> enemies;
    std::vector<Entity*> items;
    std::vector<Fireball*> fireball;
    std::vector<Entity*> effects;
    std::vector<Entity*> decor;
    std::vector<Entity*> shells;
    std::vector<Entity*> testEntities;
    GameCamera camera;  
    bool isPaused;

public:
    GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player);
    ~GameEngine();
    void resolveCollision();
    void addScore(int amount);
    void addFireBall(Fireball* fireball);
    void addEnemy(Entity* enemy);
    void addEffect(Entity* effect);
    void addShell(Entity* shell);
    void addItem(Entity* item);
    void update(float deltaTime);
    void handleCollision();
    void render(float deltaTime);
    bool run();
    float getGlobalTime();
};
extern GameEngine* globalGameEngine;

#endif