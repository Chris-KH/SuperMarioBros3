#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class SuperStarmanState : public CharacterState {
	friend class Character;
public:
	SuperStarmanState(Character* character = nullptr);
	~SuperStarmanState() = default;

	void setAnimation() override;

    void update(float deltaTime) override;

    STATE getState() const override;
};