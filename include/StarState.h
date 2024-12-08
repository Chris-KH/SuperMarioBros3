#pragma once
#include"CharacterState.h"

class StarState : public CharacterState {
	friend class Character;
public:
	virtual ~StarState() = default;

	virtual void update(const Character* character, float deltaTime) override {};
	virtual STATE getState() const override {
		return STAR;
	}
};