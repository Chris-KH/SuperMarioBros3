#pragma once
#include "Enemy.h"
#include "Collision.h"

enum GoomBaType {
	BROWN_GoomBa,
	RED_GoomBa,
	REDPARA_GoomBa,
	BROWNPARA_GoomBa,
	MICRO_GoomBa
};

class GoomBa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;

	GoomBa() = default;
	GoomBa(GoomBaType type, Vector2 position) {
		this->type = type;
		setXVelocity(SPEED);
		setYVelocity(0.f);
		setPosition(position);
		jumping = true;
		if (type == BROWN_GoomBa) {
			setAnimation("brown_goomba");
		}
		else if (type == RED_GoomBa) {
			setAnimation("brown_paragoomba");
		}
		else if (type == BROWNPARA_GoomBa) {
			setAnimation("red_goomba");
		}
		else if (type == REDPARA_GoomBa) {
			setAnimation("red_paragoomba");
		}
	}

private:
	GoomBaType type;
};
