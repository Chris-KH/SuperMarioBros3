#pragma once
#include <raylib.h>

class Entity {
private:
    Vector2 position;
    Vector2 size;
    Texture2D texture;
    Rectangle sourceRect;
    Vector2 velocity;
    float speed;
    bool isFlipped;

public:
    // Constructor
    Entity(Vector2 pos, Vector2 sz, Texture2D tex, float spd) : position(pos), size(sz), texture(tex), velocity{ 0, 0 }, speed(spd), isFlipped(false) {
        sourceRect = { 0, 0, (float)tex.width, (float)tex.height };
    }

    Rectangle getHitBox();
    void setPosition(Vector2 newPos);
    void handleInput();
    void move();
    void draw() const;
    void unloadTexture() const;
};