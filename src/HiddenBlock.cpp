#include "../include/HiddenBlock.h"

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {}

BlockType HiddenBlock::getBlockType() const {
    return HIDDEN;
}

void HiddenBlock::update(float deltaTime) {
    //PlaceHolder for HiddenBlock
}