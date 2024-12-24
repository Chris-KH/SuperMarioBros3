#ifndef BASEBLOCK_H
#define BASEBLOCK_H
#include "C:/Users/Dell/Downloads/CS202-SuperMario/lib/raylib.h"
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
//#include "Item.h"

class BaseBlock : public Entity {
public:
    BaseBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    virtual ~BaseBlock();

    EntityType getType() const;
    virtual BlockType getBlockType() const = 0;
    virtual void draw(float deltaTime);
    virtual void update(float deltaTime) override;

protected:
    Animation* sprite = nullptr;
};
#endif