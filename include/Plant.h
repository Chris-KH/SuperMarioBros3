#pragma once
#include "Enemy.h"

class Plant : public Enemy {
public:
	const float SPEED = 10.f;

	~Plant() {
		free(piranha);
		free(firePiranhaRest);
		free(firePiranhaAttack);
		piranha = nullptr;
		firePiranhaRest = nullptr;
		firePiranhaAttack = nullptr;
	}
	Plant(PlantType type = GREEN_PIRANHA, Vector2 position = {0.f, 0.f}) : Enemy(position) {
		this->type = type;
		setXVelocity(0.f);
		setYVelocity(0.f);
		setGravityAvailable(false);

		piranha = nullptr;
		firePiranhaRest = nullptr; 
		firePiranhaAttack = nullptr;

		if (type == GREEN_PIRANHA) {
			piranha = RESOURCE_MANAGER.getAnimation("green_piranha")->clone();
		}
		else if (type == GREEN_FIREPIRANHA) {
			firePiranhaRest = RESOURCE_MANAGER.getAnimation("green_firepiranha")->clone();
			firePiranhaAttack = RESOURCE_MANAGER.getAnimation("green_firepiranha_attack")->clone();
		}
	}

	EnemyType getEnemyType() const override {
		return EnemyType::PLANT;
	}

	void update(float deltaTime) override {

	}

private:
	PlantType type;
	Animation* piranha;
	Animation* firePiranhaRest; // Four orientation {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
	Animation* firePiranhaAttack; // Four orientation {0, 1, 2, 3} for {downLeft, upLeft, downRight, upRight}
};