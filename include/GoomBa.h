#pragma once
#include "Enemy.h"
#include "Collision.h"

class GameEngine;

class GoomBa : public Enemy {
private:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;
	const float TIME_PER_JUMP = 2.f;

	GoomBaType type;
	Animation* walkAnimation;
	Animation* jumpAnimation;
	bool canJump;
	float jumpTime;
public:
	GoomBa(GoomBaType type = BROWN_GoomBa, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);
	~GoomBa();

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;
	void stomped() override;

	//Test function
	/*void update(float deltaTime) override {
		if (isDead) return;
		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

		if (IsKeyDown(KEY_D)) setXVelocity(SPEED);
		else if (IsKeyDown(KEY_A)) setXVelocity(-SPEED);

		if (IsKeyDown(KEY_SPACE) && canJump) {
			setYVelocity(-JUMP_SPEED);
			setAnimation(jumpAnimation);
			setJumping(true);
			jumpTime = 0.f;
		}
		if (isJumping() == false) {
			setAnimation(walkAnimation);
			jumpTime += deltaTime;
		}
	}*/
};
