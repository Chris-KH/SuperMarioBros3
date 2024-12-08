#pragma once
#include"CharacterState.h"

class FireState : public CharacterState {
	friend class Character;
public:
	virtual ~FireState() = default;

	virtual void update(const Character* character, float deltaTime) override {};
	virtual STATE getState() const override {
		return FIRE;
	}
};