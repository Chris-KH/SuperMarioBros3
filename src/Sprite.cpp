#include "../include/Sprite.h"

Sprite::Sprite() 
    : Entity2(Vector2(0 , 0), Vector2(1, 1), Color(255, 255, 255, 255)),
	velocity({ 0, 0 }),
	acceleration({ 0, 0 }),
	maxSpeed({ 100, 100 }),
	isDead(false),
	isFlipped(false)
{}

Sprite::Sprite(Vector2 pos, Vector2 size, Color color)
    : Entity2(pos, size, color),
    velocity({ 0, 0 }), 
    acceleration({ 0, 0 }),
    maxSpeed({ 300, 500 }), 
    isDead(false), 
    isFlipped(false) 
{}

Sprite::Sprite(const Sprite& other)
    : Entity2(other),
    velocity(other.velocity),
    acceleration(other.acceleration),
    maxSpeed(other.maxSpeed),
    isDead(other.isDead),
    isFlipped(other.isFlipped)
{}


// Movement and physics methods
Vector2 Sprite::getVelocity() const { return velocity; }

void Sprite::setVelocity(Vector2 vel) { velocity = vel; }

Vector2 Sprite::getAcceleration() const { return acceleration; }

void Sprite::setAcceleration(Vector2 acc) { acceleration = acc; }

Vector2 Sprite::getMaxSpeed() const { return maxSpeed; }

void Sprite::setMaxSpeed(Vector2 max) { maxSpeed = max; }

void Sprite::update(float deltaTime) {
    // Update velocity with acceleration
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    // Clamp velocity to max speed
    if (velocity.x > maxSpeed.x) velocity.x = maxSpeed.x;
    if (velocity.y > maxSpeed.y) velocity.y = maxSpeed.y;

    // Update position with velocity
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

// Flip sprite horizontally
void Sprite::flip(bool flip) { isFlipped = flip; }

// Draw method override
void Sprite::draw() const {
    Rectangle destRect = { position.x, position.y, size.x, size.y };
    Rectangle srcRect = { 0, 0, (isFlipped ? -size.x : size.x), size.y };
    DrawRectangleRec(destRect, color); // Replace with texture drawing
}