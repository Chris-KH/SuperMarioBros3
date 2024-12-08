#pragma once
#include"CharacterState.h"

class NormalState : public CharacterState {
    friend class Character;
public:
    ~NormalState();

    void update(const Character* character, float deltaTime) override {};
    STATE getState() const override {
        return NORMAL;
    }
};