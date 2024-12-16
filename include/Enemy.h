#pragma once
#include "Sprite.h"
#include "Animation.h"

class Enemy : public Sprite {
protected:
    bool isAttacking;

    bool isAlive;

public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);
    
    virtual EntityType getType() const override { return EntityType::ENEMY; }
    
    // Override draw to use animations
    virtual void draw() const;
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime);
};