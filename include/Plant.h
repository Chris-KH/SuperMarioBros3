#pragma once
#include "Enemy.h"

class Plant : public Enemy {
public:
	enum PlantType {
		RED_PIRANHA,
		RED_FIREPIRANHA,
		GREEN_PIRANHA,
		GREEN_FIREPIRANHA
	};

	Plant() = default;
	Plant(PlantType type) {
		this->type = type;

	}
private:
	PlantType type;
};