#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"

class Hitbox {
public:
    Hitbox() {
        rect.x = 0;
        rect.y = 0;
        rect.width = 0;
        rect.height = 0;
    }
    void setPosition(int x, int y) {
        rect.x = x;
        rect.y = y;
    }
    void setSize(int width, int height) {
        rect.width = width;
        rect.height = height;
    }
<<<<<<< HEAD
    bool Hitbox::checkCollision(const Hitbox& other) const {
        return CheckCollisionRecs(rect, other.rect);
    }
=======
    //bool Hitbox::checkCollision(const Hitbox& other) const {
    //    return CheckCollisionRecs(rect, other.rect);
    //}
>>>>>>> 44191ed8dd049dea357388c0c82ddfa655517ec0

    int getX() const {
        return rect.x;
    }
    int getY() const {
        return rect.y;
    }
    int getWidth() const {
        return rect.width;
    }
    int getHeight() const {
        return rect.height;
    }

    Rectangle getRaylibRectangle() const {
        return rect;
    }

private:
    Rectangle rect;
};

#endif