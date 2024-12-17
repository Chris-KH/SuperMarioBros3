#pragma once
#include "Sprite.h"
#include "Animation.h"

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE) {

    };

    virtual ~Enemy() {

    }
    
    virtual EntityType getType() const override { return EntityType::ENEMY; }
    
    // Override draw to use animations
    virtual void draw() const {
        if (currentAnimation == nullptr) return;
        currentAnimation->render(getPosition());
    }
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime) {}

    void stomped();
    void attacked();
};