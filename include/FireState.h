#pragma once
#include"CharacterState.h"

class FireState : public CharacterState {
public:
	virtual ~FireState() = default;

	virtual void update(const Character* character) override {};
};