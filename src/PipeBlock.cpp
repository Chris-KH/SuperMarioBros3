#include "../include/PipeBlock.h"

PipeBlock::PipeBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType PipeBlock::getBlockType() const {
    return PIPE;
}

void PipeBlock::update(float deltaTime) {
    // Placeholder for pipe block behavior
}