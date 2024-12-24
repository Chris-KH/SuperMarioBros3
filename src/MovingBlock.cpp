#include "../include/MovingBlock.h"

MovingBlock::MovingBlock(Vector2 pos, Vector2 size)
    : BaseBlock(pos, size), boundLeft(pos.x), boundRight(pos.x), boundTop(pos.y), boundBottom(pos.y) {
    sprite = RESOURCE_MANAGER.getAnimation("moving_platform_block")->clone();
    setAnimation(sprite);
}

BlockType MovingBlock::getBlockType() const {
    return MOVINGBLOCK;
}

void MovingBlock::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;

    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    updateTime(deltaTime);
    currentAnimation->update(deltaTime);
    currentAnimation->render(getPosition());
}

void MovingBlock::setBounds(float left, float right, float top, float bottom) {
    Vector2 pos = getPosition();
    if (left >= right || top >= bottom) {
        TraceLog(LOG_WARNING, "Invalid bounds! Defaulting to block's current position.");
        boundLeft = pos.x;
        boundRight = pos.x;
        boundTop = pos.y;
        boundBottom = pos.y;
    }
    else {
        boundLeft = left;
        boundRight = right;
        boundTop = top;
        boundBottom = bottom;
    }
}

Vector2 MovingBlock::getVelocity() const {
    return velocity;
}


void MovingBlock::setVelocity(Vector2 newVelocity) {
    velocity = newVelocity;
}

void MovingBlock::update(float deltaTime) {
    Vector2 pos = getPosition();

    if (pos.x < boundLeft) {
        velocity.x = std::abs(velocity.x);
    }
    else if (pos.x + getSize().x > boundRight) {
        velocity.x = -std::abs(velocity.x);
    }

    if (pos.y < boundTop) {
        velocity.y = std::abs(velocity.y);
    }
    else if (pos.y + getSize().y > boundBottom) {
        velocity.y = -std::abs(velocity.y);
    }
}