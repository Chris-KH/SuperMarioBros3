#include "../include/Sprite.h"

Sprite::Sprite(Vector2 pos, Vector2 size, Color color)
    : Entity(pos, size, color),
    velocity({ 0, 0 }), 
    acceleration({ 0, 0 }),
    isDead(false),
    jumping(false),
    gravityAvailable(true)
{}

Sprite::Sprite(const Sprite& other)
    : Entity(other),
    velocity(other.velocity),
    acceleration(other.acceleration),
    isDead(other.isDead),
    jumping(other.jumping),
    gravityAvailable(other.gravityAvailable)
{}


// Movement and physics methods
const Vector2& Sprite::getVelocity() const { return velocity; }

void Sprite::setVelocity(Vector2 vel) { velocity = vel; }

const Vector2& Sprite::getAcceleration() const { return acceleration; }

void Sprite::setAcceleration(Vector2 acc) { acceleration = acc; }

void Sprite::setXVelocity(float vx) {
    velocity.x = vx;
}

void Sprite::setYVelocity(float vy) {
    velocity.y = vy;
}

void Sprite::setXAcceleration(float ax) {
    acceleration.x = ax;
}

void Sprite::setYAcceleration(float ay) {
    acceleration.y = ay;
}

void Sprite::update(float deltaTime) {

}

void Sprite::draw(float deltaTime) const {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

void Sprite::setJumping(bool value) {
    jumping = value;
}

bool Sprite::isJumping() const { return jumping; }

void Sprite::setGravity(bool gravityAvailable) {
    this->gravityAvailable = gravityAvailable;
}