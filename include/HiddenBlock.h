#ifndef HIDDENBLOCK_H
#define HIDDENBLOCK_H

#include "BaseBlock.h"

class HiddenBlock : public BaseBlock {
private:
    bool revealed = false;

public:
    HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = WHITE);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
    void reveal();
};
#endif // !HIDDENBLOCK_H
