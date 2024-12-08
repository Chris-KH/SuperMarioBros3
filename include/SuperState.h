#pragma once
#include"CharacterState.h"

class SuperState : public CharacterState {
	friend class Character;
public:
	virtual ~SuperState() = default;

	virtual void update(const Character* character, float deltaTime) override {};
	virtual STATE getState() const override {
		return SUPER;
	}
};