#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class FireStarmanState : public CharacterState {
	friend class Character;
public:
    FireStarmanState(Character* character = nullptr);
	~FireStarmanState() = default;

    void setAnimation() override;

    void update(float deltaTime) override;

    STATE getState() const override;
};