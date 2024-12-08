#pragma once
#include"CharacterState.h"

class SuperState : public CharacterState {
public:
	virtual ~SuperState() = default;

	virtual void update(const Character* character) override {};
};