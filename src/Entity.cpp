#include "../include/Entity.h"

Entity::Entity(Vector2 pos, Vector2 size)
    : position(pos), size(size) {
    currentAnimation = nullptr;
    playTime = 0.f;
    dead = false;
}

Entity::Entity(const Entity& other)
    : position(other.position), size(other.size) {
    currentAnimation = nullptr;
    playTime = 0.f;
    dead = other.dead;
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

const Vector2& Entity::getSize() const {
    return this->size;
}

const Vector2& Entity::getPosition() const {
    return this->position;
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

void Entity::setCenter(Vector2 center) {
    Vector2 oldCenter = getCenter();
    setPosition({ position.x + center.x - oldCenter.x, position.y + center.y - oldCenter.y });
}

void Entity::updateTime(float deltaTime) {
    this->playTime -= deltaTime;
    this->playTime = max(0.f, this->playTime);
}

void Entity::setAnimation(Animation* animation, float time) {
    if (playTime > 0.f) return;
    if (animation == nullptr) return;
    if (currentAnimation == animation) return;
    this->playTime = time;
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

void Entity::setAnimation(const string& name, float time) {
    Animation* cur = RESOURCE_MANAGER.getAnimation(name);
    if (cur == nullptr) return;
    setAnimation(cur, time);
}

void Entity::killEntity() {
    this->dead = true;
}

bool Entity::isDead() const {
    return this->dead;
}