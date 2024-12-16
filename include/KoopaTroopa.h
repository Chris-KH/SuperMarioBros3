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

	KoopaTroopa() = default;
	KoopaTroopa(KoopaTroopaType type) {
		this->type = type;

	}
private:
	KoopaTroopaType type;
};