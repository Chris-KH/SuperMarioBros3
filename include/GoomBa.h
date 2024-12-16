#pragma once
#include "Enemy.h"
#include "Collision.h"

class GoomBa : public Enemy {
public:
	enum GoomBaType {
		BROWN_GoomBa,
		RED_GoomBa,
		REDPARA_GoomBa,
		BROWNPARA_GoomBa,
		MICRO_GoomBa
	};

	GoomBa() = default;
	GoomBa(GoomBaType type) {
		this->type = type;

	}
private:
	GoomBaType type;
};
