#include "../include/Sprite.h"
#include "../include/GameEngine.h"
Sprite::Sprite(Vector2 pos, Vector2 size)
    : Entity(pos, size),
    velocity({ 0, 0 }), 
    jumping(false),
    gravityAvailable(true),
    collisionAvailable(true),
    orientation(RIGHT)
{}

Sprite::Sprite(const Sprite& other)
    : Entity(other),
    velocity(other.velocity),
    jumping(other.jumping),
    gravityAvailable(other.gravityAvailable),
    collisionAvailable(other.collisionAvailable),
    orientation(other.orientation)
{}


// Movement and physics methods
const Vector2& Sprite::getVelocity() const { return velocity; }

void Sprite::setVelocity(Vector2 vel) { velocity = vel; }

void Sprite::setXVelocity(float vx) {
    velocity.x = vx;
}

void Sprite::setYVelocity(float vy) {
    velocity.y = vy;
}

void Sprite::update(float deltaTime) {
    if (isDead()) return;
    if (globalGameEngine)
    {
        Vector2 bound = globalGameEngine->getBound();
        if (this->getX() > bound.x || this->getY() > bound.y)
            killEntity();
    }
}

void Sprite::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    updateTime(deltaTime);
    currentAnimation->update(deltaTime);
    currentAnimation->render(getPosition());
}

void Sprite::setJumping(bool value) {
    jumping = value;
}

bool Sprite::isJumping() const { return jumping; }

void Sprite::setGravityAvailable(bool gravityAvailable) {
    this->gravityAvailable = gravityAvailable;
}

bool Sprite::isGravityAvailable() const {
    return this->gravityAvailable;
}

void Sprite::setCollisionAvailable(bool collisionAvailable) {
    this->collisionAvailable = collisionAvailable;
}

bool Sprite::isCollisionAvailable() const {
    return this->collisionAvailable;
}

void Sprite::setOrientation(Orientation orientation) {
    this->orientation = orientation;
}

Orientation Sprite::getOrientation() const {
    return orientation;
}

bool Sprite::isIdle() const {
    return (velocity.x == 0.f && velocity.y == 0.f);
}