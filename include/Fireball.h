#pragma once
#include"Sprite.h"

enum FireballType {
	CHARACTER_FIREBALL,
	ENEMY_FIREBALL
};

class Fireball: public Sprite {
private:
	Animation* fireRight;
	Animation* fireLeft;
	FireballType type;
public:
	~Fireball() {
		free(fireRight);
		free(fireLeft);
		fireLeft = nullptr;
		fireRight = nullptr;
	}

	Fireball(Vector2 center = {0.f, 0.f}, FireballType type = CHARACTER_FIREBALL, Orientation orientation = RIGHT) {
		setCenter(center);
		this->type = type;
		this->orientation = orientation;

		fireRight = nullptr;
		fireLeft = nullptr;

		if (orientation == LEFT) fireLeft = RESOURCE_MANAGER.getAnimation("fireball_left")->clone();
		else if (orientation == RIGHT) fireRight = RESOURCE_MANAGER.getAnimation("fireball_right")->clone();

		if (orientation == LEFT) setAnimation(fireLeft);
		else if (orientation == RIGHT) setAnimation(fireRight);
	}

	const FireballType& getFireballType() const {
		this->type;
	}

	void update(float deltaTime) override {

	}

	void draw(float deltaTime = GetFrameTime()) override {

	}
};