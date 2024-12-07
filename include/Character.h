#pragma once
#include "Animation.h"
#include "Sprite.h"
//#include "Hitbox.h"

class Character : public Sprite {
protected:
    Animation idleAnimation;
    Animation runAnimation;
    Animation jumpAnimation;
    Animation fallAnimation;
    Animation duckAnimation;
    Animation slideAnimation;
    Animation attackAnimation;
    Animation powerUpAnimation;
    Animation deathAnimation;
    Animation victoryAnimation;

    // Another animation
    Animation swimmingAnimation;
    Animation climbingAnimation;
    Animation hurtAnimation;
    Animation transformAnimation;
    Animation crouchJumpAnimation;
    Animation victoryDanceAnimation;
    Animation collectCoinAnimation;
    Animation dashAnimation;
    Animation fallingAnimation;
    Animation specialMoveAnimation;

public:
    //Character(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);

    //virtual EntityType getType() const override { return EntityType::CHACRACTER; }
    //
    //// Override draw to use animations
    //void draw() const;

    //// Method to handle movement (keyboard input)
    //void move(float deltaTime);

    //// Method to handle jumping
    //void jump();

    //// Method to switch between animations
    //void switchAnimation(Animation& animation);
};

