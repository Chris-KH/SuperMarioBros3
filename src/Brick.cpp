#include "../include/Brick.h"

Brick::Brick(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {
    sprite = RESOURCE_MANAGER.getAnimation("gold_brick_block")->clone();
    setAnimation(sprite);
}

void Brick::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

BlockType Brick::getBlockType() const {
    return BRICK;
}

void Brick::update(float deltaTime) {
    currentAnimation->update(deltaTime);
}

void Brick::breakBrick() {
    isBroken = true;
}