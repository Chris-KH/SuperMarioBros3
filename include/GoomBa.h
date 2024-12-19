#pragma once
#include "Enemy.h"
#include "Collision.h"

class GoomBa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;

	~GoomBa() {
		free(walkAnimation);
		free(jumpAnimation);
		walkAnimation = nullptr;
		jumpAnimation = nullptr;
	}

	GoomBa(GoomBaType type = BROWN_GoomBa, Vector2 position = {0.f, 0.f}) : Enemy(position) {
		this->type = type;
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
		}
		else if (type == REDPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba")->clone();
			jumpAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba_jump")->clone();
		}

		setAnimation(walkAnimation);
	}

	EnemyType getEnemyType() const override {
		return EnemyType::GOOMBA;
	}

	void update(float deltaTime) override {
		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

		if (isJumping()) {
			setYPosition(getPosition().y + velocity.y * deltaTime);
		}

		currentAnimation->update(deltaTime);
	}

	void stomped() override {
		if (type == BROWN_GoomBa || type == RED_GoomBa) {
			destroySprite();
		}
		else if (type == REDPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("red_goomba")->clone();
			free(jumpAnimation);
			jumpAnimation = nullptr;
		}
		else if (type == BROWNPARA_GoomBa) {
			walkAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba")->clone();
			free(jumpAnimation);
			jumpAnimation = nullptr;
		}
	}

private:
	GoomBaType type;
	Animation* walkAnimation;
	Animation* jumpAnimation;
};
