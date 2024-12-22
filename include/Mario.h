#pragma once
#include "Character.h"

class Mario : public Character {
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;
	friend class FireState;
	friend class StarmanState;
	friend class SuperStarmanState;
	friend class FireStarmanState;
private:
	const float GROUND_ACCELERATION = 250.f;
	const float GROUND_DECCELERATION = 200.f;
	const float GROUND_SKID_DECELERATION = 800.f;

	const float MAX_RUN_VELOCITY = 400.f;

	const float JUMP_VELOCITY = 300.f;
public:
	Mario(Vector2 pos = { 0, 0 });

	CharacterType getCharacterType() const override;

	void reset();
};