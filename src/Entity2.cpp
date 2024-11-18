#include "../include/Entity2.h"

Entity2::Entity2():
    red(255),
    green(255),
    blue(255),
    alpha(255)
{}

void Entity2::setRed(unsigned red) {
    this->red = min(max(red, 0u), 255u);
}

void Entity2::setGreen(unsigned green) {
    this->green = min(max(green, 0u), 255u);
}

void Entity2::setBlue(unsigned blue) {
    this->blue = min(max(blue, 0u), 255u);
}

void Entity2::setAlphe(unsigned alpha) {
    this->alpha = min(max(alpha, 0u), 255u);
}