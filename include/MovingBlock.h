#ifndef MOVINGBLOCK_H
#define MOVINGBLOCK_H

#include "BaseBlock.h"

class MovingBlock : public BaseBlock {
private:
    Vector2 velocity = { 50.0f, 50.0f };
    float boundLeft, boundRight;
    float boundTop, boundBottom;

public:
    MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 16, 16 });
    BlockType getBlockType() const override;
    void draw(float deltaTime) override;
    void setBounds(float left, float right, float top, float bottom);
    Vector2 getVelocity() const;
    void setVelocity(Vector2 newVelocity);
    void update(float deltaTime) override;
};
#endif // !MOVINGBLOCK_H
