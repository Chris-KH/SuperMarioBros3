#pragma once

#include "raylib.h"
//#include "Hitbox.h"
#include <fstream>

enum BlockType {
    normal,
    breakable,
    moving,
    itemRelease,
    hidden,
    lava,
    pipe
};

class Block {
public:
	Block(float x, float y, float width, float height, BlockType type) : hitbox{ x, y, width, height }, velocity{0.0f, 0.0f}, type(type), isSolid(true), itemCounting(0) {}
	Rectangle getHitbox() const {
        switch (type) {
            case breakable:
            return { hitbox.x, hitbox.y, hitbox.width, 0 };
            default:
            return hitbox;
        }
    }

    void handleMoving(float deltaTime) {
        if (type == moving) {
            hitbox.x += velocity.x * deltaTime;
            hitbox.y += velocity.y * deltaTime;
        }
    }

    void hit() {
        if (!isSolid) return;
        switch (type) {
            case breakable:
            isSolid = false;
            break;

            case itemRelease:
            //xử lý itemRelease
            break;

            case hidden:
            //xử lý opacity - Fade, ColorAlpha
            break;


        }
    }

    void savetoBinaryFile(std::ofstream &file) const {
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
        file.write(reinterpret_cast<const char*>(&hitbox), sizeof(hitbox));
    }

    void loadfromBinaryFile(std::ifstream &file) {
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
        file.read(reinterpret_cast<char*>(&hitbox), sizeof(hitbox));
    }

    virtual void render() const {
        Color color = Color(0, 0, 0, 255);
        ColorAlpha(color, 0.0f);
        DrawRectangle(static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), static_cast<int>(hitbox.width), static_cast<int> (hitbox.height), Fade(color, 0));
    }

private:
	Rectangle hitbox;
    Vector2 velocity;
    BlockType type;
    bool isSolid;
    int itemCounting;
    static constexpr float bouncingHeight = 10.0f;
    static constexpr float bounceDuration = 0.1f;

    void releaseItem() {
        if (itemCounting > 0) {
            itemCounting--;
        }
        if (itemCounting == 0) {
            type = normal;
        }
    }
    
};
