#pragma once
#include "Enemy.h"

class Bloober : public Enemy {
public:
	enum BlooberType {
		NORMAL_Bloober,
		WITHKIDS_Bloober,
		BABY_Bloober
	};
};