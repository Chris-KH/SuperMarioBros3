#pragma once
#include "Character.h"

class Luigi : public Character {
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;
	friend class FireState;
	friend class StarState;
private:
	const float GROUND_ACCELERATION = 600.f;
	const float GROUND_DEACCELERATION = 2000.f;

	const float MAX_WALK_VELOCITY = 350.f;
	const float MAX_RUN_VELOCITY = 700.f;

	const float JUMP_VELOCITY = 900.f;
public:
	Luigi(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE);

	CHACRACTER getCharacterType() const override;

	void update(float deltaTime) override;

	void onKey(KeyboardKey key, bool pressed) override;

	void reset();
};