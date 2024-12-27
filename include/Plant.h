#ifndef PLANT_H
#define PLANT_H

#include "Enemy.h"

class Fireball;

class Plant : public Enemy {
public:
	enum Phase {
		WAIT_PHASE,
		ATTACK_PHASE,
		EXIT_PHASE,
		ENTER_PHASE
	};

private:
	PlantType type;
	Animation* piranha;
	Animation* firePiranhaRest; // Four direction {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
	Animation* firePiranhaAttack; // Four direction {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
	Orientation direction;
	Phase phase;
	Character* player;
	float timer;

public:
	const float SPEED = 25.f;
	const float WAIT_TIME = 3.f;
	const float ATTACK_TIME = 2.f;

	~Plant();

	Plant(PlantType type = GREEN_PIRANHA, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT, Character* player = nullptr);

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;

	void draw(float deltaTime = GetFrameTime()) override;

	Vector2 getCentral();

	void setPlayerForFireball(Character* player);
	void setDirection();
};
#endif