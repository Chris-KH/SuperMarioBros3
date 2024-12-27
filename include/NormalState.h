#ifndef NORMALSTATE_H
#define NORMALSTATE_H

#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class NormalState : public CharacterState {
    friend class Character;
public:
    NormalState(Character* character = nullptr);
    ~NormalState() = default;

    void setAnimation() override;
    void update(float deltaTime) override;
    STATE getState() const override;
};
#endif