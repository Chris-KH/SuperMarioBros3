#ifndef HITBOX_H
#define HITBOX_H

#include "../lib/raylib.h"

class Hitbox {
public:
    Hitbox() {
        rect.x = 0;
        rect.y = 0;
        rect.width = 0;
        rect.height = 0;
    }
    void setPosition(float x, float y) {
        rect.x = x;
        rect.y = y;
    }
    void setSize(float width, float height) {
        rect.width = width;
        rect.height = height;
    }
    
    //bool Hitbox::checkCollision(const Hitbox& other) const {
    //    return CheckCollisionRecs(rect, other.rect);
    //}

    float getX() const {
        return rect.x;
    }
    float getY() const {
        return rect.y;
    }
    float getWidth() const {
        return rect.width;
    }
    float getHeight() const {
        return rect.height;
    }

    Rectangle getRaylibRectangle() const {
        return rect;
    }

private:
    Rectangle rect;
};

#endif
