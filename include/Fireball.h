#pragma once
#include"Sprite.h"

enum FireballType {
	CHARACTER_FIREBALL,
	ENEMY_FIREBALL
};

class Fireball: public Sprite {
private:
	const float ENEMY_FIREBALL_LIFETIME = 5.f;
	const float ENEMY_FIREBALL_SPEED = 1000.f;

	const float CHARACTER_FIREBALL_SPEED = 80.f;

	Animation* fireRight;
	Animation* fireLeft;
	FireballType type;

	float delayTime;
	bool soundEffect;
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
		this->soundEffect = false;

		fireLeft = RESOURCE_MANAGER.getAnimation("fireball_left")->clone();
		fireRight = RESOURCE_MANAGER.getAnimation("fireball_right")->clone();

		//fireLeft->setScale(5.f);
		//fireRight->setScale(5.f);

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
		this->delayTime = -delayTime;
	}

	const float& getDelayTime() const {
		return -delayTime;
	}

	void calculateFireballVelocity(const Vector2& fireballPos, const Vector2& playerPos, float speed = 0.f) {
		if (speed == 0.f) {
			if (type == ENEMY_FIREBALL) speed = ENEMY_FIREBALL_SPEED;
			else if (type == CHARACTER_FIREBALL) speed = CHARACTER_FIREBALL_SPEED;
		}

		Vector2 direction = { playerPos.x - fireballPos.x, playerPos.y - fireballPos.y };

		float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

		Vector2 velocity = { (direction.x / magnitude) * speed, (direction.y / magnitude) * speed };
		
		if (velocity.x < 0) setAnimation(fireLeft);
		else if (velocity.x > 0) setAnimation(fireRight);
		
		delayVelocity = velocity;
	}

	void update(float deltaTime) override {
		if (isDead()) return;
		if (type == CHARACTER_FIREBALL) {
			if (delayTime >= 0.f) {
				setXVelocity(CHARACTER_FIREBALL_SPEED);
				if (isGravityAvailable() == true) setYVelocity(getVelocity().y + GRAVITY * deltaTime);
			}

			delayTime += deltaTime;
		}
		else if (type == ENEMY_FIREBALL) {
			if (delayTime >= ENEMY_FIREBALL_LIFETIME) {
				killEntity();
				return;
			}
			if (delayTime >= 0.f) {
				setVelocity(delayVelocity);
				if (soundEffect == false) RESOURCE_MANAGER.playSound("shot.wav");
				soundEffect = true;
			}
			
			delayTime += deltaTime;
		}
	}
};