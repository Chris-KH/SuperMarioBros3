#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class StarState : public CharacterState {
	friend class Character;
public:
	~StarState();

    virtual void setState(Character* character) {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        if (dynamic_cast<Mario*>(character) != nullptr) {

        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {

        }
    }
	void update(Character* character, float deltaTime) override {};
	STATE getState() const override {
		return STAR;
	}
};