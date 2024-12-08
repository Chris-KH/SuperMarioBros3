#pragma once
#include "Character.h"

class Mario : public Character {
private:

public:

	CHACRACTER getCharacterType() const override {
		return CHACRACTER::MARIO;
	}

	void update(float deltaTime) override {

	}

	void onKey(KeyboardKey key, bool pressed) override {

	}
};