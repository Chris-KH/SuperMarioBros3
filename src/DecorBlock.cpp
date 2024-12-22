#include "../include/DecorBlock.h"

DecorBlock::DecorBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {
    sprite = RESOURCE_MANAGER.getAnimation("pipe_block_head")->clone();
    setAnimation(sprite);
}

void DecorBlock::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

BlockType DecorBlock::getBlockType() const {
    return DECOR;
}

void DecorBlock::update(float deltaTime) {
    // Placeholder for decor block behavior
}