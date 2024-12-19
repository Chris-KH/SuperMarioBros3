#include "../include/Entity.h"

Entity::Entity(Vector2 pos, Vector2 size, Color color)
    : position(pos), size(size), color(color) {
    currentAnimation = nullptr;
}

Entity::Entity(const Entity& other)
    : position(other.position), size(other.size), color(other.color) {
    currentAnimation = nullptr;
}

Entity::~Entity() {
    currentAnimation = nullptr;
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

float Entity::getCenterX() const {
    return position.x + size.x / 2.f;
}

float Entity::getCenterY() const {
    return position.y + size.y / 2.f;
}

float Entity::getBottom() const {
    return position.y + size.y;
}

float Entity::getLeft() const {
    return position.x;
}

float Entity::getRight() const {
    return position.x + size.x;
}

float Entity::getTop() const {
    return position.y;
}

Vector2 Entity::getCenter() const {
    return { getCenterX(), getCenterY() };
}

void Entity::setPosition(Vector2 pos) { position = pos; }

void Entity::setXPosition(float x) { position.x = x; }

void Entity::setYPosition(float y) { position.y = y; }

void Entity::setSize(Vector2 sz) { size = sz; }

void Entity::setColor(Color col) { color = col; }

void Entity::setCenter(Vector2 center) {
    Vector2 oldCenter = getCenter();
    setPosition({ position.x + center.x - oldCenter.x, position.y + center.y - oldCenter.y });
}

void Entity::setAnimation(Animation* animation) {
    if (currentAnimation == animation) return;
    float diffHeight = 0.f;
    if (currentAnimation != nullptr && currentAnimation != animation) {
        diffHeight = currentAnimation->getSize().y - animation->getSize().y;
        currentAnimation->reset();
    }
    currentAnimation = animation;
    if (currentAnimation == nullptr) return;
    this->setYPosition(position.y + diffHeight);
    this->setSize(currentAnimation->getSize());
};

void Entity::setAnimation(const string& name) {
    Animation* cur = RESOURCE_MANAGER.getAnimation(name);
    if (cur == nullptr) return;
    setAnimation(cur);
}