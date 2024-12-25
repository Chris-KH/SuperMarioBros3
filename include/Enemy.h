#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Animation.h"

class Character;
class Fireball;

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;

    Vector2 boudary; //The x-axis range that enemy can move (y-axis for vertical plant)
    const float DEAD_TIME = 0.5f;
    const float DEAD_INITIAL_VELOCITY_Y = 300.f;
    const float DEAD_INITIAL_VELOCITY_X = 100.f;
    const int ENEMY_POINT = 100;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });

    virtual ~Enemy() = default;
    
    virtual EntityType getType() const override;

    virtual EnemyType getEnemyType() const = 0;
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime) override = 0;

    Orientation getRandomOrientation();

    virtual void setBoudary(Vector2 boundary);

    virtual const Vector2& getBoundary() const;

    virtual void stomped();
    virtual void attacked(Orientation direction = RIGHT);
    virtual void kicked(Orientation direction) {};
    void collisionWithFireball(Fireball* fireball);
};

#endif // !ENEMY_H

