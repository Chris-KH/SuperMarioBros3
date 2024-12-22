#pragma once
#include"Sprite.h"

class Block;
class Character;

class Fireball: public Sprite {
private:
	const float ENEMY_FIREBALL_LIFETIME = 5.f;
	const float ENEMY_FIREBALL_SPEED = 1000.f;

	const float CHARACTER_FIREBALL_SPEED = 150.f;
	const float BOUNCE_VELOCITY = -200.f;

	Animation* fireRight;
	Animation* fireLeft;
	FireballType type;

	float delayTime;
	bool soundEffect;
	Vector2 delayVelocity;
public:
	
	Fireball(Vector2 center = { 0.f, 0.f }, FireballType type = CHARACTER_FIREBALL, Orientation orientation = RIGHT);
	~Fireball();

	const FireballType& getFireballType() const;

	EntityType getType() const override;

	void setDelayTime(float delayTime);

	float getDelayTime() const;

	void calculateFireballVelocity(const Vector2& fireballPos, const Vector2& playerPos, float speed = 0.f);
	void setCharacterPositionBall(const Character* character);

	void update(float deltaTime) override;

	void collisionWithBlock(const Block* block, Edge edge);
};