#include "../include/PipeBlock.h"

PipeBlock::PipeBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {}

BlockType PipeBlock::getBlockType() const {
    return PIPE;
}

void PipeBlock::update(float deltaTime) {
    // Placeholder for pipe block behavior
}