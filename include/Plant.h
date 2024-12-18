#pragma once
#include "Enemy.h"

class Plant : public Enemy {
public:
	Plant() = default;
	Plant(PlantType type = GREEN_PIRANHA, Vector2 position = {0.f, 0.f}) {
		this->type = type;

	}

	EnemyType getEnemyType() const override {
		return EnemyType::PLANT;
	}
private:
	PlantType type;
};