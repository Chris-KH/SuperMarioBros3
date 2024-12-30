#ifndef ITEMBLOCK_H
#define ITEMBLOCK_H

#include "BaseBlock.h"

class Sprite;
class Character;
class Fireball;

class ItemBlock : public BaseBlock {
private:
    bool hasItem = true;
    ItemType item;
    int subType;
    bool isBouncing = false;
    float bounceTime = 0.0f;
    const float bounceHeight = 8.0f;
    const float bounceDuration = 0.2f;
    float OgY;
public:
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    BlockType getBlockType() const override;
    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void releaseItem(const Sprite* object);
    void setItem(ItemType item, int subtype);
};

#endif