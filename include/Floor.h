#ifndef FLOOR_H
#define FLOOR_H

#include "BaseBlock.h"

class Floor : public BaseBlock {
public:
    Floor(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};
#endif // !FLOOR_H
