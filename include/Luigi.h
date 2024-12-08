#pragma once
#include "Character.h"

class Luigi : public Character {
private:
	const float GROUND_ACCELERATION = 900.f;
	const float GROUND_DEACCELERATION = 2000.f;

	const float MAX_WALK_VELOCITY = 350.f;
	const float MAX_RUN_VELOCITY = 900.f;

	const float JUMP_VELOCITY = 900.f;
public:
	Luigi(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE) : Character(pos, size, col) {};

	CHACRACTER getCharacterType() const override {
		return CHACRACTER::LUIGI;
	}

	void update(float deltaTime) override {

	}

	void onKey(KeyboardKey key, bool pressed) override {

	}

	void reset() {
		Character::reset();
	}
};