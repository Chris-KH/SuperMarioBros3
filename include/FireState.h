#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class Fireball;

class FireState : public CharacterState {
	friend class Character;
public:
	FireState(Character* character = nullptr);

	~FireState() = default;
	void setAnimation() override;
	void update(float deltaTime) override;
	STATE getState() const override;
};