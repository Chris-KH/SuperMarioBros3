#pragma once
#include "Enemy.h"
#include "Collision.h"

class GoomBa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;
	const float TIME_PER_JUMP = 2.f;

	~GoomBa() {
		free(walkAnimation);
		free(jumpAnimation);
		walkAnimation = nullptr;
		jumpAnimation = nullptr;
	}

	GoomBa(GoomBaType type = BROWN_GoomBa, Vector2 position = {0.f, 0.f}, Orientation orientation = RIGHT) : Enemy(position) {
		this->type = type;
		this->jumpTime = 0.f;
		this->canJump = false;
		this->orientation = orientation;
		setXVelocity(orientation == RIGHT ? SPEED : -SPEED);
		setYVelocity(0.f);

		walkAnimation = nullptr;
		jumpAnimation = nullptr;

		if (type == BROWN_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba")->clone();
		}
		else if (type == RED_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("red_goomba")->clone();
		}
		else if (type == BROWNPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("brown_paragoomba")->clone();
			jumpAnimation = RESOURCE_MANAGER.getAnimation("brown_paragoomba_jump")->clone();
			this->canJump = true;
		}
		else if (type == REDPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba")->clone();
			jumpAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba_jump")->clone();
			this->canJump = true;
		}

		setAnimation(walkAnimation);
	}

	EnemyType getEnemyType() const override {
		return EnemyType::GOOMBA;
	}

	void update(float deltaTime) override {
		if (isDead) return;
	
		if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
		else if (getPosition().x >= getBoundary().y) setOrientation(LEFT);
	
		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);
		
		if (jumpTime >= TIME_PER_JUMP && canJump) {
			setYVelocity(-JUMP_SPEED);
			setAnimation(jumpAnimation);
			setJumping(true);
			jumpTime = 0.f;
		}
		else if (getBottom() >= 500.f) {
			setYVelocity(0.f);
			setYPosition(500.f - getSize().y);
			jumping = false;
		}

		if (orientation) setXVelocity(SPEED);
		else setXVelocity(-SPEED);

		
		if (isJumping() == false) {
			setAnimation(walkAnimation);
			jumpTime += deltaTime;
		}
	}

	void stomped() override {
		if (type == BROWN_GoomBa || type == RED_GoomBa) {
			destroySprite();
		}
		else if (type == REDPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("red_goomba")->clone();
			canJump = false;
			jumpTime = 0.f;
			free(jumpAnimation);
			jumpAnimation = nullptr;
		}
		else if (type == BROWNPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba")->clone();
			canJump = false;
			jumpTime = 0.f;
			free(jumpAnimation);
			jumpAnimation = nullptr;
		}
	}

private:
	GoomBaType type;
	Animation* walkAnimation;
	Animation* jumpAnimation;
	bool canJump;
	float jumpTime;
};
