#pragma once
#include "Animation.h"
#include "Sprite.h"
#include "Hitbox.h"

class Character : public Sprite {
protected:
    Animation runAnimation;
    Animation jumpAnimation;
    Animation idleAnimation;
    Animation* currentAnimation;

public:
    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE);

    // Override draw to use animations
    void draw() const;

    // Method to handle movement (keyboard input)
    void move(float deltaTime);

    // Method to handle jumping
    void jump();

    // Method to switch between animations
    void switchAnimation(Animation& animation);
};

