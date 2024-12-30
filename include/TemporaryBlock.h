#ifndef TEMPORARYBLOCK_H
#define TEMPORARYBLOCK_H

#include "BaseBlock.h"

class TemporaryBlock : public BaseBlock {
private:
    float lifeTime;
    bool isDying;
    bool dead;

public:
    TemporaryBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    BlockType getBlockType() const override;
    void update();
};
#endif
