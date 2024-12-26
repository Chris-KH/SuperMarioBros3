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
	Animation* deadAnimation;
	bool canJump;
	float jumpTime;
public:
	GoomBa(GoomBaType type = BROWN_GoomBa, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);
	~GoomBa();

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;
	void attacked(Orientation direction = RIGHT) override;
	void stomped() override;
};
