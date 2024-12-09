#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class FireState : public CharacterState {
	friend class Character;
public:
	~FireState();

    virtual void setState(Character* character) {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        if (dynamic_cast<Mario*>(character) != nullptr) {
            //character->idle = RESOURCE_MANAGER.getAnimation("firemario_idle")
            character->idleLeft = RESOURCE_MANAGER.getAnimation("firemario_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("firemario_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("firemario_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("firemario_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("firemario_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("firemario_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("firemario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("firemario_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("firemario_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("firemario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("firemario_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("firemario_fall_right");
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("fireluigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("fireluigi_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("fireluigi_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("fireluigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("fireluigi_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("fireluigi_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("fireluigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("fireluigi_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("fireluigi_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("fireluigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("fireluigi_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("fireluigi_fall_right");
        }
    }
	void update(Character* character, float deltaTime) override {};
	STATE getState() const override {
		return FIRE;
	}
};