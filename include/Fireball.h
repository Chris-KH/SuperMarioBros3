#pragma once
#include"Sprite.h"

enum FireballType {
	CHARACTER_FIREBALL,
	ENEMY_FIREBALL
};

class Fireball: public Sprite {
private:
	const float ENEMY_FIREBALL_SPEED = 100.f;

	Animation* fireRight;
	Animation* fireLeft;
	FireballType type;

	float delayTime;
	Vector2 delayVelocity;
public:
	~Fireball() {
		free(fireRight);
		free(fireLeft);
		fireLeft = nullptr;
		fireRight = nullptr;
	}

	Fireball(Vector2 center = {0.f, 0.f}, FireballType type = CHARACTER_FIREBALL, Orientation orientation = RIGHT) {
		this->type = type;
		this->orientation = orientation;
		this->delayTime = 0.f;
		this->delayVelocity = { 0.f, 0.f };

		fireRight = nullptr;
		fireLeft = nullptr;

		if (orientation == LEFT) fireLeft = RESOURCE_MANAGER.getAnimation("fireball_left")->clone();
		else if (orientation == RIGHT) fireRight = RESOURCE_MANAGER.getAnimation("fireball_right")->clone();

		if (orientation == LEFT) setAnimation(fireLeft);
		else if (orientation == RIGHT) setAnimation(fireRight);

		setCenter(center);
	}

	const FireballType& getFireballType() const {
		this->type;
	}

	EntityType getType() const override {
		return EntityType::FIREBALL;
	}

	void setDelayTime(float delayTime) {
		this->delayTime = delayTime;
	}

	const float& getDelayTime() const {
		return delayTime;
	}

	void calculateFireballVelocity(const Vector2& fireballPos, const Vector2& playerPos, float speed = 0.f) {
		if (speed == 0.f) {
			speed = ENEMY_FIREBALL_SPEED;
		}

		Vector2 direction = { playerPos.x - fireballPos.x, playerPos.y - fireballPos.y };

		float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

		Vector2 velocity = { (direction.x / magnitude) * speed, (direction.y / magnitude) * speed };
		
		if (velocity.x < 0) setAnimation(fireLeft);
		else if (velocity.x > 0) setAnimation(fireRight);
		
		delayVelocity = velocity;
	}

	void update(float deltaTime) override {
		if (type == CHARACTER_FIREBALL) {

		}
		else if (type == ENEMY_FIREBALL) {
			if (delayTime <= 0.f) {
				setVelocity(delayVelocity);
			}
			else {
				delayTime -= deltaTime;
			}
		}
	}
};