#ifndef BRICK_H
#define BRICK_H

#include "BaseBlock.h"

class Brick : public BaseBlock {
public:
    Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    void draw(float deltaTime) override;
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
    void breakBrick();
private:
    bool isBroken = false;
};
#endif // !BRICK_H
