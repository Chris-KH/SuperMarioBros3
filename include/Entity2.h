#pragma once
#include <raylib.h>
#include "Animation.h"

class Entity2 {
public:
    Entity2() : red(255), green(255), blue(255), alpha(255) {}
    virtual ~Entity2() {}

    //Get the x coordinate of the entity.
    virtual float getX() const = 0;
    //Get the y coordinate of the entity.
    virtual float getY() const = 0;
    //Get the width of the bounding box (rectangle)
    virtual float getWidth() const = 0;
    //Get the length of the bounding box (rectangle)
    virtual float getHeight() const = 0;
    //Get box (rectangle)
    virtual Rectangle getRectangle() const = 0;

    // RGBA Color setters and getters
    void setRed(unsigned r);
    unsigned getRed() const { return red; }

    void setGreen(unsigned g);
    unsigned getGreen() const { return green; }

    void setBlue(unsigned b);
    unsigned getBlue() const { return blue; }

    void setAlpha(unsigned a);
    unsigned getAlpha() const { return alpha; }
protected:
    unsigned red, green, blue, alpha;
};

