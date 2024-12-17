#pragma once
#include "Sprite.h"
#include "Animation.h"

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;

    const float GROUND = 800.f;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE) {
        stompable = false;
        kickable = false;
    };

    virtual ~Enemy() {

    }
    
    virtual EntityType getType() const override { return EntityType::ENEMY; }
    
    // Override draw to use animations
    virtual void draw(float deltaTime) const {
        if (currentAnimation == nullptr) return;
        currentAnimation->render(getPosition());
    }
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime) {
        currentAnimation->update(deltaTime);
        setYVelocity(velocity.y + GRAVITY * deltaTime);

        if (isJumping()) {
            setYPosition(getPosition().y + velocity.y * deltaTime);
        }

        if (getBottom() >= 500.f) {
            setYVelocity(0.f);
            setYPosition(500.f - getSize().y);
            jumping = false;
        }

        setXPosition(getPosition().x + velocity.x * deltaTime);
        setYPosition(getPosition().y + velocity.y * deltaTime);
    }

    void stomped();
    void attacked();
};