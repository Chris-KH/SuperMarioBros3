#include "../include/Character.h"

Character::Character(Vector2 pos, Vector2 size, Color col)
    : Sprite(pos, size, col),
    runAnimation(), jumpAnimation(), idleAnimation()
{
    // Initialize animations
    // Assuming you have the texture loaded elsewhere and frames are added
    runAnimation.addFrame({ 0, 0, 32, 32 }, { 0, 0 }, 100);
    jumpAnimation.addFrame({ 32, 0, 32, 32 }, { 0, 0 }, 100);
    idleAnimation.addFrame({ 64, 0, 32, 32 }, { 0, 0 }, 100);

    currentAnimation = &idleAnimation; // Default to idle animation
}

void Character::draw() const {
    currentAnimation->render(position, false, false, 1.0f); // Render current animation frame
}

void Character::move(float deltaTime) {
    // Handle movement based on input (e.g., left/right movement)
    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x = 5.0f;
        switchAnimation(runAnimation);
    }
    else if (IsKeyDown(KEY_LEFT)) {
        velocity.x = -5.0f;
        switchAnimation(runAnimation);
    }
    else {
        velocity.x = 0;
        switchAnimation(idleAnimation);
    }

    // Update position based on velocity
    position.x += velocity.x * deltaTime;
}

void Character::jump() {
    // Handle jump logic
    if (IsKeyPressed(KEY_SPACE)) {
        velocity.y = -10.0f; // Apply jump force
        switchAnimation(jumpAnimation); // Switch to jump animation
    }
}

void Character::switchAnimation(Animation& animation) {
    if (currentAnimation != &animation) {
        currentAnimation = &animation;
        currentAnimation->reset(); // Reset animation to the first frame
    }
}