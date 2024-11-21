#include "../include/Sprite.h"

Sprite::Sprite() :
	position({ 0, 0 }),
	size({ 0, 0 }),
	velocity({ 0, 0 }),
	acceloration({ 0, 0 }),
	maxSpeed({ 0, 0 }),
	isDead(false),
	isFlipped(false)
{
}

float Sprite::getX() const {
	return position.x;
}

float Sprite::getY() const {
	return position.y;
}

float Sprite::getWidth() const {
	return size.x;
}

float Sprite::getHeight() const {
	return size.y;
}

void Sprite::setX(float x) {
	this->position.x = x;
}

void Sprite::setY(float y) {
	this->position.y = y;
}

void Sprite::setWidth(float width) {
	this->size.x = width;
}

void Sprite::setHeight(float height) {
	this->size.y = height;
}

float Sprite::getMaximumXSpeed() const {
	return maxSpeed.x;
}

float Sprite::getMaximumYSpeed() const {
	return maxSpeed.y;
}

void Sprite::setMaximumXSpeed(float speed) {
	this->maxSpeed.x = abs(speed);
}

void Sprite::setMaximumYSpeed(float speed) {
	this->maxSpeed.y = abs(speed);
}

float Sprite::getXVelocity() const {
	return velocity.x;
}

float Sprite::getYVelocity() const {
	return velocity.y;
}

float Sprite::getXAcceleration() const {
	return acceloration.x;
}

float Sprite::getYAcceleration() const {
	return acceloration.y;
}

void Sprite::setXVelocity(float vx) {
	this->velocity.x = vx;
}

void Sprite::setYVelocity(float vy) {
	this->velocity.y = vy;
}

void Sprite::setXAcceleration(float ax) {
	this->acceloration.x = ax;
}

void Sprite::setYAcceleration(float ay) {
	this->acceloration.y = ay;
}