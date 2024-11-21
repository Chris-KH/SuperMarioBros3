#pragma once
#include <raylib.h>
#include "Animation.h"

class Entity2 {
public:
    Entity2();
    virtual ~Entity2() {}

    //Get the x coordinate of the entity.
    virtual double getX() const = 0;
    //Get the y coordinate of the entity.
    virtual double getY() const = 0;
    //Get the width of the bounding box (rectangle)
    virtual double getWidth() const = 0;
    //Get the length of the bounding box (rectangle)
    virtual double getLength() const = 0;
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

