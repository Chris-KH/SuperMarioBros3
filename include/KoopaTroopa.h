#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy {
public:
	enum KoopaTroopaType {
		GREEN_KoopaTroopa,
		RED_KoopaTroopa,
		GREEN_KoopaParaTroopa,
		RED_KoopaParaTroopa
	};

	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;

	KoopaTroopa() = default;
	KoopaTroopa(KoopaTroopaType type) {
		this->type = type;
		setXVelocity(SPEED);
		if (type == GREEN_KoopaTroopa) {
			setAnimation("");
		}
		else if (type == RED_KoopaTroopa) {

		}
		else if (type == GREEN_KoopaParaTroopa) {

		}
		else if (type == RED_KoopaParaTroopa) {

		}
	}

	void update(float deltaTime) override {

	}
private:
	KoopaTroopaType type;
};