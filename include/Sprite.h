#include "Entity2.h"

//For moving object
class Sprite : public Entity2 {
private:
	Vector2 position;     // Position (x, y)
	Vector2 size;         // Size (width, height)
	Vector2 velocity;     // Velocity (dx, dy)
	Vector2 acceleration; // Acceleration (ax, ay)
	Vector2 maxSpeed;     // Maximum speed (x, y)

	bool isDead;   // Indicates if the sprite is "dead"
	bool isFlipped; // Indicates if the sprite is flipped horizontally
public:
	Sprite();
	
	virtual ~Sprite() = default;

	//void disableCollisions();
	//void disableGravity();

	float getX() const override;
	float getY() const override;
	float getWidth() const override;
	float getHeight() const override;

	void setX(float x); 
	void setY(float y); 
	void setWidth(float width); 
	void setHeight(float height);

	float getMaximumXSpeed() const;
	float getMaximumYSpeed() const;
	void setMaximumXSpeed(float speed);
	void setMaximumYSpeed(float speed);

	
	float getXVelocity() const;
	float getYVelocity() const;
	float getXAcceleration() const;
	float getYAcceleration() const;
	

	void setXVelocity(float vx);
	void setYVelocity(float vy);
	void setXAcceleration(float ax);
	void setYAcceleration(float ay);
	
	
	//bool isFlying() const;
	//bool isHeld() const;
	//bool isHoldingEnabled() const;
	//void kill(); ///@todo rename to destroy()
	//
	//void setCollisionsEnabled(bool enabled);
	//void setDeathBoundaryEnabled(bool enabled);
	//void setGravityEnabled(bool enabled);
	//
	//void setHolding(bool held, Player* player = nullptr);
	//void setLayer(int layer);
	//void setLeft(float x);
	//void setRight(float x);
	//void setTop(float y);
	//void setBottom(float y);
	//void setCenterX(float x);
	//void setCenterY(float y);
};