#pragma once
#include "Character.h"

class Luigi : public Character {
private:
public:

	CHACRACTER getCharacterType() const override {
		return CHACRACTER::LUIGI;
	}

	void update(float deltaTime) override {

	}

	void onKey(KeyboardKey key, bool pressed) override {

	}
};