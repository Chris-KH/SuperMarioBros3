#include "../include/Entity2.h"

Entity2::Entity2(Vector2 pos, Vector2 size, Color color)
    : position(pos), size(size), color(color) {
}

Entity2::Entity2(const Entity2& other)
    : position(other.position), size(other.size), color(other.color) {
}

float Entity2::getX() const { return position.x; }

float Entity2::getY() const { return position.y; }

float Entity2::getWidth() const { return size.x; }

float Entity2::getHeight() const { return size.y; }

Rectangle Entity2::getRectangle() const {
    return { position.x, position.y, size.x, size.y };
}

void Entity2::setPosition(Vector2 pos) { position = pos; }

void Entity2::setSize(Vector2 sz) { size = sz; }

void Entity2::setColor(Color col) { color = col; }