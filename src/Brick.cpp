#include "../include/Brick.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

Brick::Brick(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {
    sprite = RESOURCE_MANAGER.getAnimation("../assets/Animation/tiles1.txt/gold_brick_block")->clone();
    setAnimation(sprite);
}

void Brick::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

BlockType Brick::getBlockType() const {
    return BRICK;
}

void Brick::update(float deltaTime) {
    currentAnimation->update(deltaTime);
}

void Brick::breakBrick() {
    killEntity();
    Effect* breakEffect = new Effect(RESOURCE_MANAGER.getAnimation("../assets/Animation/tiles1.txt/gold_brick_block_broken")->clone(), getPosition(), true, 0.f);
    globalGameEngine->addEffect(breakEffect);

    Effect* textEffect = new TextEffect("100", getCenter());
    globalGameEngine->addEffect(textEffect);

    globalGameEngine->addScore(100);
    RESOURCE_MANAGER.playSound("../assets/Sound/break_brick_block.wav");
}