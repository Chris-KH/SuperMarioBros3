#ifndef BLOCK_H
#define BLOCK_H
#include "../lib/raylib.h"
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

class Floor : public BaseBlock {
public:
    Floor(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = GREEN);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};

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

class SolidBlock : public BaseBlock {
public:
    SolidBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = DARKBROWN);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};

class MovingBlock : public BaseBlock {
private:
    Vector2 velocity = { 50.0f, 50.0f };
    float boundLeft, boundRight;
    float boundTop, boundBottom;

public:
    MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 16, 16 }, Color color = DARKGRAY);
    BlockType getBlockType() const override;
    void draw(float deltaTime) override;
    void setBounds(float left, float right, float top, float bottom);
    Vector2 getVelocity() const;
    void setVelocity(Vector2 newVelocity);
    void update(float deltaTime) override;
};

class ItemBlock : public BaseBlock {
private:
    bool hasItem = true;
    ItemType item;
    int subType;
    bool isBouncing = false; // Flag to track if the block is bouncing
    float bounceTime = 0.0f; // Timer for controlling the bounce
    const float bounceHeight = 8.0f; // Height to move up during the bounce
    const float bounceDuration = 0.2f;
    float OgY;
public:
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = YELLOW);
    BlockType getBlockType() const override;
    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void releaseItem();
    void setItem(ItemType item,int subtype);
};

class HiddenBlock : public BaseBlock {
private:
    bool revealed = false;

public:
    HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = WHITE);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
    void reveal();
};

class SpikeBlock : public BaseBlock {
public:
    SpikeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLACK);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};

class PipeBlock : public BaseBlock {
public:
    PipeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = DARKGREEN);
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};

class DecorBlock : public BaseBlock {
public:
    DecorBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK);
    void draw(float deltaTime) override;
    BlockType getBlockType() const override;
    void update(float deltaTime) override;
};

class TemporaryBlock : public BaseBlock {
private:
    float lifeTime;
    bool isDying;
    bool dead;

public:
    TemporaryBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK);
    BlockType getBlockType() const override;
    void update();
};
#endif