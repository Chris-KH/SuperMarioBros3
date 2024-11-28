#include "../include/Enemy.h"

Enemy::Enemy(Vector2 pos, Vector2 size, Color col)
    : Sprite(pos, size, col),
    walkAnimation(), attackAnimation(),
    currentAnimation(&walkAnimation)
{
    // Initialize animations for the enemy (assuming you load textures and frames)
    walkAnimation.addFrame({ 0, 0, 32, 32 }, { 0, 0 }, 100);
    attackAnimation.addFrame({ 32, 0, 32, 32 }, { 0, 0 }, 100);

    currentAnimation = &walkAnimation; // Default to walk animation
}

void Enemy::draw() const {
    currentAnimation->render(position, false, false, 1.0f);
}

void Enemy::move(float deltaTime) {
    // Handle enemy movement (AI)
    velocity.x = 3.0f; // Example enemy speed
    position.x += velocity.x * deltaTime;
}

void Enemy::switchAnimation(Animation& animation) {
    if (currentAnimation != &animation) {
        currentAnimation = &animation;
        currentAnimation->reset(); // Reset animation to the first frame
    }
}