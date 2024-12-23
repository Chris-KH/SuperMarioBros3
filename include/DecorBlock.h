#ifndef DECORBLOCK_H
#define DECORBLOCK_H

#include "BaseBlock.h"

class DecorBlock : public BaseBlock {
public:
    DecorBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK);
    void draw(float deltaTime) override;
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};
#endif // !DECORBLOCK_H
