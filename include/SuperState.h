#pragma once
#include"CharacterState.h"

class SuperState : public CharacterState {
	friend class Character;
public:
	~SuperState();

	void update(const Character* character, float deltaTime) override {};
	STATE getState() const override {
		return SUPER;
	}
};