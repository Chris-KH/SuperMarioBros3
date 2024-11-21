#include "Entity2.h"

class Sprite : public Entity2 {
private:
	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceloration;
	Vector2 maxSpeed;

	bool isDead;
	bool isFlipped;
public:
	Sprite();
	
	virtual ~Sprite() = default;

	void disableCollisions();
	void disableGravity();

	double getX() const;
	double getY() const;
	double getWidth() const;
	double getHeight() const;

	void setX(double x); 
	void setY(double y); 
	void setWidth(double width); 
	void setHeight(double height);

	double getMaximumXSpeed() const;
	double getMaximumYSpeed() const;
	void setMaximumXSpeed(double speed);
	void setMaximumYSpeed(double speed);

	
	double getXVelocity() const;
	double getYVelocity() const;
	double getXAcceleration() const;
	double getYAcceleration() const;
	

	void setXVelocity(double vx);
	void setYVelocity(double vy);
	void setXAcceleration(double ax);
	void setYAcceleration(double ay);
	
	
	bool isFlying() const;
	bool isHeld() const;
	bool isHoldingEnabled() const;
	void kill(); ///@todo rename to destroy()
	
	void setCollisionsEnabled(bool enabled);
	void setDeathBoundaryEnabled(bool enabled);
	void setGravityEnabled(bool enabled);
	
	//void setHolding(bool held, Player* player = nullptr);
	void setLayer(int layer);
	void setLeft(double x);
	void setRight(double x);
	void setTop(double y);
	void setBottom(double y);
	void setCenterX(double x);
	void setCenterY(double y);
};

Sprite::Sprite(): 
	position({ 0, 0 }),
	size({ 0, 0 }),
	velocity({ 0, 0 }),
	acceloration({ 0, 0 }),
	maxSpeed({ 0, 0 }),
	isDead(false),
	isFlipped(false)
{}

double Sprite::getX() const {
	return position.x;
}

double Sprite::getY() const {
	return position.y;
}

double Sprite::getWidth() const {
	return size.x;
}

double Sprite::getHeight() const {
	return size.y;
}

void Sprite::setX(double x) {
	this->position.x = x;
}

void Sprite::setY(double y) {
	this->position.y = y;
}

void Sprite::setWidth(double width) {
	this->size.x = width;
}

void Sprite::setHeight(double height) {
	this->size.y = height;
}

double Sprite::getMaximumXSpeed() const {
	return maxSpeed.x;
}

double Sprite::getMaximumYSpeed() const {
	return maxSpeed.y;
} 

void Sprite::setMaximumXSpeed(double speed) {
	this->maxSpeed.x = abs(speed);
}

void Sprite::setMaximumYSpeed(double speed) {
	this->maxSpeed.y = abs(speed);
}

double Sprite::getXVelocity() const {
	return velocity.x;
}

double Sprite::getYVelocity() const {
	return velocity.y;
}

double Sprite::getXAcceleration() const {
	return acceloration.x;
}

double Sprite::getYAcceleration() const {
	return acceloration.y;
}

void Sprite::setXVelocity(double vx) {
	this->velocity.x = vx;
}

void Sprite::setYVelocity(double vy) {
	this->velocity.y = vy;
}

void Sprite::setXAcceleration(double ax) {
	this->acceloration.x = ax;
}

void Sprite::setYAcceleration(double ay) {
	this->acceloration.y = ay;
}