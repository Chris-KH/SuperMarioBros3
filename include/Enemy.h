#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Animation.h"

class Character;

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;

    Vector2 boudary; //The x-axis range that enemy can move (y-axis for vertical plant)
    const float DEAD_TIME = 0.5f;
    const int ENEMY_POINT = 100;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);

    virtual ~Enemy() = default;
    
    virtual EntityType getType() const override;

    virtual EnemyType getEnemyType() const = 0;
    
    // Override draw to use animations
    virtual void draw(float deltaTime = GetFrameTime()) override;
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime) override;

    Orientation getRandomOrientation();

    virtual void setBoudary(Vector2 boundary);

    virtual const Vector2& getBoundary() const;

    virtual void stomped();
    virtual void attacked();
    virtual void kicked(Orientation direction) {};
};

#endif // !ENEMY_H

