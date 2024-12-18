#pragma once
#include "Enemy.h"

class Plant : public Enemy {
public:
	const float SPEED = 10.f;

	~Plant();

	Plant(PlantType type = GREEN_PIRANHA, Vector2 position = { 0.f, 0.f }, Character* player = nullptr);

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;

	void draw(float deltaTime = GetFrameTime()) override;

	Vector2 getCentral();

	void setDirection();

private:
	PlantType type;
	Animation* piranha;
	Animation* firePiranhaRest; // Four direction {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
	Animation* firePiranhaAttack; // Four direction {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
	Orientation direction;
	Character* player;
};