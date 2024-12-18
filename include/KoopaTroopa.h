#pragma once
#include "Enemy.h"

class KoopaTroopa : public Enemy {
public:
	const float SPEED = 50.f;
	const float JUMP_SPEED = 200.f;

	KoopaTroopa() = default;
	~KoopaTroopa() {
		delete walkLeft;
		delete walkRight;
		delete jumpLeft;
		delete jumpRight;
		walkLeft = nullptr;
		walkRight = nullptr;
		jumpLeft = nullptr;
		jumpRight = nullptr;
	}
	KoopaTroopa(KoopaTroopaType type = GREEN_KoopaTroopa, Vector2 position = {0.f, 0.f}) {
		this->type = type;
		setXVelocity(SPEED);
		walkLeft = nullptr;
		walkRight = nullptr;
		jumpLeft = nullptr;
		jumpRight = nullptr;

		if (type == GREEN_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkLeft")->clone();
			walkRight = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkRight")->clone(); 
		}
		else if (type == RED_KoopaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkRight")->clone(); 
		}
		else if (type == GREEN_KoopaParaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpRight")->clone(); 
		}
		else if (type == RED_KoopaParaTroopa) {
			walkLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkLeft")->clone(); 
			walkRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkRight")->clone(); 
			jumpLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpLeft")->clone(); 
			jumpRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpRight")->clone(); 
		}

		
	}

	EnemyType getEnemyType() const override {
		return EnemyType::KOOPATROOPA;
	}
private:
	KoopaTroopaType type;
	Animation* walkLeft;
	Animation* walkRight;
	Animation* jumpLeft;
	Animation* jumpRight;
};