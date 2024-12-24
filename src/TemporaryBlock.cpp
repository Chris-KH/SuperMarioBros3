#include "../include/TemporaryBlock.h"

TemporaryBlock::TemporaryBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size), lifeTime(1.5), isDying(false), dead(false) {}

BlockType TemporaryBlock::getBlockType() const {
    return TEMPBLOCK;
}

void TemporaryBlock::update() {
    if (!dead && isDying) {
        float deltaTime = GetFrameTime();
        lifeTime -= deltaTime;
        if (lifeTime <= 0) {
            dead = true;
        }
    }
}
