#include "../include/HiddenBlock.h"

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType HiddenBlock::getBlockType() const {
    return HIDDEN;
}

void HiddenBlock::update(float deltaTime) {
    if (revealed) {
        setColor(ORANGE);
    }
}

void HiddenBlock::reveal()
{
}