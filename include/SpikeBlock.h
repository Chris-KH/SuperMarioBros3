#ifndef SPIKEBLOCK_H
#define SPIKEBLOCK_H

#include "BaseBlock.h"

class SpikeBlock : public BaseBlock {
public:
    SpikeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLACK);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};
#endif // !SPIKEBLOCK_H
