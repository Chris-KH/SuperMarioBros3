#include "../include/DecorBlock.h"

DecorBlock::DecorBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {
    sprite = RESOURCE_MANAGER.getAnimation("../assets/Animation/miscellaneous.txt/pipe_block_head")->clone();
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