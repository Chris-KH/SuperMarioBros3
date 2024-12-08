#pragma once
#include"CharacterState.h"

class NormalState : public CharacterState {
    friend class Character;
public:
    virtual ~NormalState() = default;

    virtual void update(const Character* character, float deltaTime) override {};
    virtual STATE getState() const override {
        return NORMAL;
    }
};