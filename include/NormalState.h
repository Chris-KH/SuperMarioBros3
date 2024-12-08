#pragma once
#include"CharacterState.h"

class NormalState : public CharacterState {
public:
    virtual ~NormalState() = default;

    virtual void update(const Character* character) override {};
};