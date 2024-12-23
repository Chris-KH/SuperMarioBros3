#ifndef BRICK_H
#define BRICK_H

#include "BaseBlock.h"

class Brick : public BaseBlock {
private:
    bool isBroken = false;

public:
    Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BROWN);
    void draw(float deltaTime) override;
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
    void breakBrick();
};
#endif // !BRICK_H