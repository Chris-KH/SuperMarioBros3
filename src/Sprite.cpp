﻿#include "../include/Sprite.h"

Sprite::Sprite(Vector2 pos, Vector2 size, Color color)
    : Entity(pos, size, color),
    velocity({ 0, 0 }), 
    acceleration({ 0, 0 }),
    maxSpeed({ 300, 500 }), 
    isDead(false)
{}

Sprite::Sprite(const Sprite& other)
    : Entity(other),
    velocity(other.velocity),
    acceleration(other.acceleration),
    maxSpeed(other.maxSpeed),
    isDead(other.isDead)
{}


// Movement and physics methods
const Vector2& Sprite::getVelocity() const { return velocity; }

void Sprite::setVelocity(Vector2 vel) { velocity = vel; }

const Vector2& Sprite::getAcceleration() const { return acceleration; }

void Sprite::setAcceleration(Vector2 acc) { acceleration = acc; }

const Vector2& Sprite::getMaxSpeed() const { return maxSpeed; }

void Sprite::setMaxSpeed(Vector2 max) { maxSpeed = max; }

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

void Sprite::setXMaxSpeed(float maxX) {
    maxSpeed.x = maxX;
}

void Sprite::setYMaxSpeed(float maxY) {
    maxSpeed.y = maxY;
}

void Sprite::update(float deltaTime) {
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;

    // Clamp the velocity to maxSpeed
    if (fabs(velocity.x) > maxSpeed.x) {
        velocity.x = (velocity.x > 0) ? maxSpeed.x : -maxSpeed.x;
    }
    if (fabs(velocity.y) > maxSpeed.y) {
        velocity.y = (velocity.y > 0) ? maxSpeed.y : -maxSpeed.y;
    }

    setPosition(Vector2(getPosition().x + velocity.x * deltaTime, getPosition().y + velocity.y * deltaTime));
}

// Draw method override
void Sprite::draw() const {
    Rectangle destRect = { getPosition().x, getPosition().y, getSize().x, getSize().y};
    Rectangle srcRect = { 0, 0, getSize().x, getSize().y };
    DrawRectangleRec(destRect, getColor()); // Replace with texture drawing
}