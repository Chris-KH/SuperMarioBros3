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
};