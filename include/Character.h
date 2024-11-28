#pragma once

#include "Sprite.h"
#include "Hitbox.h"

class Character : public Sprite {
private:
    Vector2 velocity;
    float gravity;
    bool isGrounded, isJumping;
    Hitbox hitbox;

public:
    Character(float x, float y, float width, float height) : Sprite() {}

};

