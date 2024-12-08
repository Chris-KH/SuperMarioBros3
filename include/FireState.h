#pragma once
#include"CharacterState.h"

class FireState : public CharacterState {
	friend class Character;
public:
	~FireState();

	void update(const Character* character, float deltaTime) override {};
	STATE getState() const override {
		return FIRE;
	}
};