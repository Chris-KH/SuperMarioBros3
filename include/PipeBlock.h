#ifndef PIPEBLOCK_H
#define PIPEBLOCK_H

#include "BaseBlock.h"

class PipeBlock : public BaseBlock {
public:
    PipeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};
#endif // !PIPEBLOCK
