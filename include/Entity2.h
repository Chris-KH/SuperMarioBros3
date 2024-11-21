#pragma once
#include <raylib.h>
#include "Animation.h"

class Entity2 {
public:
    Entity2();
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

    //Get red in RGBA
    void setRed(unsigned red);
    //Get green in RGBA
    void setGreen(unsigned green);
    //Get blue in RGBA
    void setBlue(unsigned blue);
    //Get alpha (opacity) in RGBA
    void setAlphe(unsigned alpha);
private:
    unsigned red;
    unsigned green;
    unsigned blue;
    unsigned alpha;

};

