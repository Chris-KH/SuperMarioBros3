#pragma once
#include"CharacterState.h"
#include"Character.h"
#include"Mario.h"
#include"Luigi.h"

class NormalState : public CharacterState {
    friend class Character;
public:
    ~NormalState();

    virtual void setState(Character* character) {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        if (dynamic_cast<Mario*>(character) != nullptr) {
            //character->idle = RESOURCE_MANAGER.getAnimation("mario_idle")
            character->idleLeft = RESOURCE_MANAGER.getAnimation("mario_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("mario_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("mario_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("mario_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("mario_jump_left");
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("mario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("mario_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("mario_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("mario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("mario_jump_right");
            character->fallRight = nullptr;
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("luigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("luigi_idle_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("luigi_idle_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("luigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("luigi_jump_left");
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("luigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("luigi_idle_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("luigi_idle_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("luigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("luigi_jump_right");
            character->fallRight = nullptr;
        }
    }
    void update(Character* character, float deltaTime) override {}
    STATE getState() const override {
        return NORMAL;
    }
};