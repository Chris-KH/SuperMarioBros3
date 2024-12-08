#pragma once
#include"CharacterState.h"

class StarState : public CharacterState {
	friend class Character;
public:
	~StarState();

	void update(const Character* character, float deltaTime) override {};
	STATE getState() const override {
		return STAR;
	}
};