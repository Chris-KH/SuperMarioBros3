#pragma once
#include "Sprite.h"
#include "Animation.h"

class Enemy : public Sprite {
protected:
    bool stompable;
    bool kickable;

    Rectangle boudary; //The rectangle that enemy can move

    const float GROUND = 800.f;
public:
    Enemy(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color col = WHITE) {
        stompable = false;
        kickable = false;
        jumping = false;

        boudary = { 0.f, 0.f, 0.f, 0.f };
        setPosition(pos);
    };

    virtual ~Enemy() {

    }
    
    virtual EntityType getType() const override { return EntityType::ENEMY; }

    virtual EnemyType getEnemyType() const = 0;
    
    // Override draw to use animations
    virtual void draw(float deltaTime = GetFrameTime()) {
        if (currentAnimation == nullptr) return;
        setXPosition(getPosition().x + velocity.x * deltaTime);
        setYPosition(getPosition().y + velocity.y * deltaTime);
        currentAnimation->render(getPosition());
    }
    
    // Method to move enemy (AI-controlled)
    virtual void update(float deltaTime) {
        currentAnimation->update(deltaTime);
        if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

        if (isJumping()) {
            setYPosition(getPosition().y + velocity.y * deltaTime);
        }

        if (getBottom() >= 500.f) {
            setYVelocity(0.f);
            setYPosition(500.f - getSize().y);
            jumping = false;
        }
    }

    Orientation getRandomOrientation() {
        random_device rd;  
        mt19937 gen(rd()); 
        uniform_int_distribution<> distr(0, 1);

        if (distr(gen) % 2 == 0) return RIGHT;
        return LEFT;
    }

    virtual void setBoudary(Rectangle rect) {
        this->boudary = rect;
    }

    virtual Rectangle getBoundary() const {
        return boudary;
    }

    //void stomped();
    //void attacked();
};