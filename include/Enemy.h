#pragma once
#include "Sprite.h"
#include "Animation.h"

class Character;

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;

    Rectangle boudary; //The rectangle that enemy can move

    const float GROUND = 800.f;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);

    virtual ~Enemy() = default;
    
    virtual EntityType getType() const override;

    virtual EnemyType getEnemyType() const = 0;
    
    // Override draw to use animations
    virtual void draw(float deltaTime = GetFrameTime());
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime);

    Orientation getRandomOrientation();

    virtual void setBoudary(Rectangle rect);

    virtual Rectangle getBoundary() const;

    void stomped();
    void attacked();
};