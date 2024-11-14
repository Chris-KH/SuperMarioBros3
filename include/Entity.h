#pragma once
#include<raylib.h>
#include "Strategy.h"

class Block {
public:
    Rectangle hitbox;
    Block(float x, float y, float width, float height)
        : hitbox{ x, y, width, height } {}
};
class Entity {
public:
    Rectangle hitbox;
    ICollisionStrategy* collisionStrategy;
    float speed;  // Movement speed

    Entity(float x, float y, float width, float height, float speed = 200.0f)
        : hitbox{ x, y, width, height }, collisionStrategy(nullptr), speed(speed) {}

    void setCollisionStrategy(ICollisionStrategy* strategy) {
        collisionStrategy = strategy;
    }

    bool checkCollision(const Block& block) {
        if (collisionStrategy)
            return collisionStrategy->collides(*this, block);
        return false;
    }

    void move(float deltaTime) {
        // Use arrow keys or WASD for movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) hitbox.x += speed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) hitbox.x -= speed * deltaTime;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) hitbox.y += speed * deltaTime;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) hitbox.y -= speed * deltaTime;
    }
};



