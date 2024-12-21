#pragma once
#include "Entity.h"

//For moving object
class Sprite : public Entity {
protected:
    Vector2 velocity;      // Velocity vector (dx, dy)
    Vector2 acceleration;  // Acceleration vector (ax, ay)
    bool jumping;
    Orientation orientation; 

    bool gravityAvailable;
    bool collisionAvailable;

    const float GRAVITY = 600.f;
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

    virtual bool isJumping() const;
    virtual void setJumping(bool value);
    virtual void setGravityAvailable(bool gravityAvailable);
    virtual bool isGravityAvailable() const;
    virtual void setCollisionAvailable(bool collisionAvailable);
    virtual bool isCollisionAvailable() const;
    virtual void setOrientation(Orientation orientation);
    virtual Orientation getOrientation() const;
    virtual bool isIdle() const;

    virtual void update(float deltaTime) override;
    virtual void draw(float deltaTime = GetFrameTime()) override;
};