#include "../include/Floor.h"

Floor::Floor(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType Floor::getBlockType() const {
    return FLOOR;
}

void Floor::update(float deltaTime) {
    // Static floor has no dynamic behavior
}