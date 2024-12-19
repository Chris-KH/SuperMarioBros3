#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;

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
	KoopaTroopa(KoopaTroopaType type = GREEN_KoopaTroopa, Vector2 position = {0.f, 0.f}) : Enemy(position) {
		this->type = type;
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
		else if (type == GREEN_KoopaParaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpRight")->clone(); 
		}
		else if (type == RED_KoopaParaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpRight")->clone(); 
		}

		
	}

	EnemyType getEnemyType() const override {
		return EnemyType::KOOPATROOPA;
	}

	void update(float deltaTime) override {
		
		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

		if (isJumping()) {
			setYPosition(getPosition().y + velocity.y * deltaTime);
		}

		currentAnimation->update(deltaTime);
	}

	void stomped() override {
		if (type == GREEN_KoopaTroopa || type == RED_KoopaTroopa) {
			destroySprite();
		}
		else if (type == GREEN_KoopaParaTroopa) {

		}
		else if (type == RED_KoopaParaTroopa) {

		}
	}

private:
	KoopaTroopaType type;
	Animation* walkLeft;
	Animation* walkRight;
	Animation* jumpLeft;
	Animation* jumpRight;
};