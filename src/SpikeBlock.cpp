#include "../include/SpikeBlock.h"

SpikeBlock::SpikeBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {}

BlockType SpikeBlock::getBlockType() const {
    return SPIKE;
}

void SpikeBlock::update(float deltaTime) {
    // Placeholder for spike block behavior
}