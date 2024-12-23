#ifndef BLOCK_H
#define BLOCK_H
#include "raylib.h"
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
//#include "Item.h"

class BaseBlock : public Entity {
public:
    BaseBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = ORANGE);
    virtual ~BaseBlock();

    EntityType getType() const;
    virtual BlockType getBlockType() const = 0;
    virtual void draw(float deltaTime);
    virtual void update(float deltaTime) override;

protected:
    Animation* sprite = nullptr;
};
#endif