#ifndef STARMANSTATE_H
#define STARMANSTATE_H

#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class StarmanState : public CharacterState {
	friend class Character;
public:
	StarmanState(Character* character = nullptr);
	~StarmanState() = default;

	virtual void setAnimation() override;
    void update(float deltaTime) override;

    STATE getState() const override;
};
#endif