#pragma once
#include "Character.h"

class Mario : public Character {
private:
	const float GROUND_ACCELERATION = 1000.f;
	const float GROUND_DEACCELERATION = 2000.f;
	
	const float MAX_WALK_VELOCITY = 400.f;
	const float MAX_RUN_VELOCITY = 1000.f;

	const float JUMP_VELOCITY = 700.f;
public:
	Mario(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE) : Character(pos, size, col) {};

	CHACRACTER getCharacterType() const override {
		return CHACRACTER::MARIO;
	}

	void update(float deltaTime) override {
		state->update(this, deltaTime);
	}

	void onKey(KeyboardKey key, bool pressed) override {
		if (isDead()) return;

		if (key == KEY_SPACE) {
			if (pressed && !isJumping()) {
				setYVelocity(JUMP_VELOCITY);

				RESOURCE_MANAGER.playSound("jump.wav");
			}
		}
		else if (key == KEY_D) {
			if (pressed) {
				orientation = true;
			}
		}
		else if (key == KEY_A) {
			if (pressed) {
				orientation = false;
			}
		}
	}

	void reset() {
		Character::reset();
	}
};