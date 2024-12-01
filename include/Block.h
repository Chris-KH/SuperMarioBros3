#pragma once

#include "raylib.h"
//#include "Hitbox.h"
#include <fstream>
#include <string>

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
	Block(float x, float y, float width, float height, BlockType type, const std::string& texturePath = "") : hitbox{ x, y, width, height }, velocity{0.0f, 0.0f}, type(type), isSolid(true), itemCounting(0) {
        if (!texturePath.empty()) {
            texture = LoadTexture(texturePath.c_str());
            loadTexture = true;
        } else {
            loadTexture = false;
        }
    }

    ~Block() {
        if (loadTexture) {
            UnloadTexture(texture);
        }
    }

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
            //Phải có Item trước
            break;

            case hidden:
            type = normal;
            isSolid = true;
            break;

        }
    }

    void savetoBinaryFile(std::ofstream &file) const {
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
        file.write(reinterpret_cast<const char*>(&hitbox), sizeof(hitbox));
        file.write(reinterpret_cast<const char*>(&isSolid), sizeof(isSolid));
        file.write(reinterpret_cast<const char*>(&itemCounting), sizeof(itemCounting));
    }

    void loadfromBinaryFile(std::ifstream &file) {
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
        file.read(reinterpret_cast<char*>(&hitbox), sizeof(hitbox));
        file.read(reinterpret_cast<char*>(&isSolid), sizeof(isSolid));
        file.read(reinterpret_cast<char*>(&itemCounting), sizeof(itemCounting));
    }

    virtual void render() const {
        if (loadTexture) {
            DrawTexture(texture, static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), WHITE);
        } else {
            Color color = GetColor(type);
            DrawRectangle(static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), static_cast<int>(hitbox.width), static_cast<int>(hitbox.height), color);
        }
    }

private:
	Rectangle hitbox;
    Vector2 velocity;
    BlockType type;
    bool isSolid;
    int itemCounting;
    Texture2D texture;
    bool loadTexture;

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

    Color GetColor(BlockType type) const {
        switch (type) {
            case normal: return GRAY;
            case breakable: return RED;
            case moving: return BROWN;
            case itemRelease: return YELLOW;
            case hidden: return Fade(GRAY, 1.0f);
            case lava: return ORANGE;
            case pipe: return GREEN;
        }
    }    
};