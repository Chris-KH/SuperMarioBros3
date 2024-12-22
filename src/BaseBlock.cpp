#include"../include/BaseBlock.h"
#include "../include/Global.h"
#include "../include/ItemFactory.h"
#include "../include/GameEngine.h"

BaseBlock::BaseBlock(Vector2 pos, Vector2 size, Color color) : Entity(pos, size, color), sprite(nullptr) {}

BaseBlock::~BaseBlock() {
    if (sprite)
        delete sprite;
}

EntityType BaseBlock::getType() const {
    return BLOCK;
}

void BaseBlock::draw(float deltaTime) {
    // Placeholder for drawing logic
}

void BaseBlock::update(float deltaTime) {
    // Placeholder for update logic
}
