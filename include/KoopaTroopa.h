#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;
	const float TIME_PER_JUMP = 2.f;

	~KoopaTroopa() {
		free(walkLeft);
		free(walkRight);
		free(jumpLeft);
		free(jumpRight);
		walkLeft = nullptr;
		walkRight = nullptr;
		jumpLeft = nullptr;
		jumpRight = nullptr;
	}
	KoopaTroopa(KoopaTroopaType type = GREEN_KoopaTroopa, Vector2 position = {0.f, 0.f}, Orientation orientation = RIGHT) : Enemy(position) {
		this->type = type;
		this->jumpTime = 0.f;
		this->canJump = false;
		this->orientation = orientation;
		setXVelocity(orientation == RIGHT ? SPEED : -SPEED);
		setYVelocity(0.f);

		walkLeft = nullptr;
		walkRight = nullptr;
		jumpLeft = nullptr;
		jumpRight = nullptr;

		if (type == GREEN_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkLeft")->clone();
			walkRight = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkRight")->clone(); 
		}
		else if (type == RED_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkRight")->clone(); 
		}
		else if (type == GREENPARA_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpRight")->clone();
			this->canJump = true;
		}
		else if (type == REDPARA_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpRight")->clone(); 
			this->canJump = true;
		}
		
		
	}

	EnemyType getEnemyType() const override {
		return EnemyType::KOOPATROOPA;
	}

	void update(float deltaTime) override {
		if (isDead) return;

		if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
		else if (getPosition().x >= getBoundary().y) setOrientation(LEFT);

		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

		if (jumpTime >= TIME_PER_JUMP && canJump) {
			setYVelocity(-JUMP_SPEED);
			if (orientation) setAnimation(jumpRight);
			else setAnimation(jumpLeft);
			setJumping(true);
			jumpTime = 0.f;
		}
		//else if (getBottom() >= 500.f) {
		//	setYVelocity(0.f);
		//	setYPosition(500.f - getSize().y);
		//	jumping = false;
		//}

		if (orientation) setXVelocity(SPEED);
		else setXVelocity(-SPEED);
		
		if (isJumping() == false) {
			if (orientation) setAnimation(walkRight);
			else setAnimation(walkLeft);
			jumpTime += deltaTime;
		}
	}

	void stomped() override {
		if (type == GREEN_KoopaTroopa || type == RED_KoopaTroopa) {
			destroySprite();
			//Create a Shell enemy
		}
		else if (type == GREENPARA_KoopaTroopa) {
			type = GREEN_KoopaTroopa;
			free(jumpLeft);
			free(jumpRight);
			free(walkLeft);
			free(walkRight);
			jumpLeft = nullptr;
			jumpRight = nullptr;
			walkLeft = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkLeft")->clone();
			walkRight = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkRight")->clone();
			canJump = false;
			jumpTime = 0.f;
		}
		else if (type == REDPARA_KoopaTroopa) {
			type = GREEN_KoopaTroopa;
			free(jumpLeft);
			free(jumpRight);
			free(walkLeft);
			free(walkRight);
			jumpLeft = nullptr;
			jumpRight = nullptr;
			walkLeft = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkLeft")->clone();
			walkRight = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkRight")->clone();
			canJump = false;
			jumpTime = 0.f;
		}
	}

private:
	KoopaTroopaType type;
	Animation* walkLeft;
	Animation* walkRight;
	Animation* jumpLeft;
	Animation* jumpRight;
	bool canJump;
	float jumpTime;
};