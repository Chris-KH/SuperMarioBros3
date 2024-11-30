#pragma once
#include "Sprite.h"
#include "Animation.h"

class Enemy : public Sprite {
protected:
    Animation walkAnimation;
    Animation attackAnimation;
    Animation idleAnimation;
    Animation jumpAnimation;
    Animation* currentAnimation;

    bool isJumping;
    bool isAttacking;
    bool isWalking;

public:
    //Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);

    //virtual EntityType getType() const override { return EntityType::ENEMY; }

    //// Override draw to use animations
    //void draw() const;

    //// Method to move enemy (AI-controlled)
    //void move(float deltaTime);

    //// Method to switch between animations
    //void switchAnimation(Animation& animation);
};