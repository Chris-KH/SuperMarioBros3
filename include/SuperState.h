#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class SuperState : public CharacterState {
	friend class Character;
public:
	~SuperState();

    virtual void setState(Character* character) {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        if (dynamic_cast<Mario*>(character) != nullptr) {
            //character->idle = RESOURCE_MANAGER.getAnimation("supermario_idle")
            character->idleLeft = RESOURCE_MANAGER.getAnimation("supermario_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("supermario_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("supermario_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("supermario_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("supermario_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("supermario_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("supermario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("supermario_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("supermario_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("supermario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("supermario_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("supermario_fall_right");
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("superluigi_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("superluigi_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("superluigi_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("superluigi_fall_right");
        }
    }	
    void update(Character* character, float deltaTime) override {};
	STATE getState() const override {
		return SUPER;
	}
};