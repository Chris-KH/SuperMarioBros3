#pragma once
#include <raylib.h>
#include "Animation.h"

class Entity2 {
protected:
    Vector2 position; // Position of the entity
    Vector2 size;     // Size of the entity
    Color color;      // RGBA color of the entity
public:
    Entity2(Vector2 pos = { 0, 0 }, Vector2 sz = { 1, 1 }, Color col = Color(255, 255, 255, 255));
    Entity2(const Entity2& other);

    virtual ~Entity2() {}

    // Getters
    virtual float getX() const;
    virtual float getY() const;
    virtual float getWidth() const;
    virtual float getHeight() const;
    virtual Rectangle getRectangle() const;

    // Setters
    virtual void setPosition(Vector2 pos);
    virtual void setSize(Vector2 sz);
    virtual void setColor(Color col);

    // Pure virtual draw function
    virtual void draw() const = 0;
};

