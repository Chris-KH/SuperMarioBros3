#include "../include/SolidBlock.h"

SolidBlock::SolidBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType SolidBlock::getBlockType() const {
    return SOLIDBLOCK;
}

void SolidBlock::update(float deltaTime) {
    // No behavior for solid blocks
}