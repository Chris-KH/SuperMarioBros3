#pragma once
#include "Character.h"

class Luigi : public Character {
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;
	friend class FireState;
	friend class StarmanState;
	friend class SuperStarmanState;
	friend class FireStarmanState;
private:
	const float GROUND_ACCELERATION = 200.f;
	const float GROUND_DECCELERATION = 200.f;
	const float GROUND_SKID_DECELERATION = 700.f;

	const float MAX_RUN_VELOCITY = 350.f;

	const float JUMP_VELOCITY = 330.f;
public:
	Luigi(Vector2 pos = { 0, 0 });

	CharacterType getCharacterType() const override;

	void update(float deltaTime) override;

	void onKey(KeyboardKey key, bool pressed) override;

	void reset();
};