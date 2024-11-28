#include "../include/Entity.h"

Entity::Entity(Vector2 pos, Vector2 size, Color color)
    : position(pos), size(size), color(color) {
}

Entity::Entity(const Entity& other)
    : position(other.position), size(other.size), color(other.color) {
}

float Entity::getX() const { return position.x; }

float Entity::getY() const { return position.y; }

float Entity::getWidth() const { return size.x; }

float Entity::getHeight() const { return size.y; }

Rectangle Entity::getRectangle() const {
    return { position.x, position.y, size.x, size.y };
}

Vector2 Entity::getSize() const {
    return this->size;
}

Vector2 Entity::getPosition() const {
    return this->position;
}

Color Entity::getColor() const {
    return this->color;
}

void Entity::setPosition(Vector2 pos) { position = pos; }

void Entity::setSize(Vector2 sz) { size = sz; }

void Entity::setColor(Color col) { color = col; }