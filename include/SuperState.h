#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class SuperState : public CharacterState {
	friend class Character;
public:
	SuperState(Character* character = nullptr) : CharacterState(character) {
		setAnimation();
	}
	~SuperState() = default;

    void setAnimation() override;
	void update(float deltaTime) override;
	STATE getState() const override;
};