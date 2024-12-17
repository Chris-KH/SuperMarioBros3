#pragma once
#include "Entity.h"

//For moving object
class Sprite : public Entity {
protected:
    Vector2 velocity;      // Velocity vector (dx, dy)
    Vector2 acceleration;  // Acceleration vector (ax, ay)
    bool isDead;           // Indicates if the sprite is "dead"
    bool jumping;

    bool gravityAvailable;

    const float GRAVITY = 800.f;
public:
    Sprite(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = WHITE);
    Sprite(const Sprite& other);

    virtual ~Sprite() = default;
    virtual EntityType getType() const = 0;

    // Movement and physics methods
    const Vector2& getVelocity() const;
    void setVelocity(Vector2 vel);

    const Vector2& getAcceleration() const;
    void setAcceleration(Vector2 acc);

    void setXVelocity(float vx);
    void setYVelocity(float vx);
    void setXAcceleration(float ax);
    void setYAcceleration(float yx);

    void destroySprite() {
        this->isDead = true;
    }

    virtual bool isJumping() const;
    virtual void setJumping(bool value);
    virtual void setGravity(bool gravityAvailable);

    virtual void update(float deltaTime);
    virtual void draw() const;
};