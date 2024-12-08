#pragma once
#include"CharacterState.h"

class StarState : public CharacterState {
public:
	virtual ~StarState() = default;

	virtual void update(const Character* character) override {};
};