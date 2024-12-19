#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class SuperState : public CharacterState {
	friend class Character;
public:
	~SuperState() = default;

    virtual void setState(Character* character);
	void update(Character* character, float deltaTime) override;
	STATE getState() const override;
};