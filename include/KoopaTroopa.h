#ifndef KOOPATROOPA_H
#define KOOPATROOPA_H

#include "Enemy.h"

class GameEngine;

class KoopaTroopa : public Enemy {
private:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 10.f;
	const float TIME_PER_JUMP = 2.f;

	KoopaTroopaType type;
	Animation* walkLeft;
	Animation* walkRight;
	Animation* jumpLeft;
	Animation* jumpRight;
	bool canJump;
	float jumpTime;

public:
	KoopaTroopa(KoopaTroopaType type = GREEN_KoopaTroopa, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);

	~KoopaTroopa();

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;

	void stomped() override;
	void attacked(Orientation direction = RIGHT) override;
};

#endif // !ENEMY_H