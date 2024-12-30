#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H

#include "BaseBlock.h"

class SolidBlock : public BaseBlock {
public:
    SolidBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};
#endif
