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
            character->walkLeft = RESOURCE_MANAGER.getAnimation("mario_walk_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("mario_run_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("mario_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("mario_jump_left");
            character->flyLeft = RESOURCE_MANAGER.getAnimation("mario_fly_left");
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("mario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("mario_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("mario_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("mario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("mario_jump_right");
            character->flyRight = RESOURCE_MANAGER.getAnimation("mario_fly_right");
            character->fallRight = nullptr;
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("luigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("luigi_walk_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("luigi_run_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("luigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("luigi_jump_left");
            character->flyLeft = RESOURCE_MANAGER.getAnimation("luigi_fly_left");
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("luigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("luigi_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("luigi_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("luigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("luigi_jump_right");
            character->flyRight = RESOURCE_MANAGER.getAnimation("luigi_fly_right");
            character->fallRight = nullptr;
        }
    }

    void update(Character* character, float deltaTime) override {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        float deceleration, acceleration, gravity, jump_velocity, max_run_velocity, max_walk_velocity;
        gravity = character->GRAVITY;
        if (dynamic_cast<Mario*>(character) != nullptr) {
            Mario* mario = dynamic_cast<Mario*>(character);
            deceleration = mario->GROUND_DEACCELERATION;
            acceleration = mario->GROUND_ACCELERATION;
            jump_velocity = mario->JUMP_VELOCITY;
            max_run_velocity = mario->MAX_RUN_VELOCITY;
            max_walk_velocity = mario->MAX_WALK_VELOCITY;
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            Luigi* luigi = dynamic_cast<Luigi*>(character);
            deceleration = luigi->GROUND_DEACCELERATION;
            acceleration = luigi->GROUND_ACCELERATION;
            jump_velocity = luigi->JUMP_VELOCITY;
            max_run_velocity = luigi->MAX_RUN_VELOCITY;
            max_walk_velocity = luigi->MAX_WALK_VELOCITY;
        }


        //Logic update
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
            if (character->velocity.x < 0) {
                if (character->isJumping() == false) character->setAnimation(character->stopLeft);
                character->setXVelocity(character->getVelocity().x + deceleration * deltaTime);
                if (character->velocity.x > 0) character->setXVelocity(max_walk_velocity);
            }
            else {
                if (IsKeyDown(KEY_LEFT_SHIFT)) character->setXVelocity(character->getVelocity().x + acceleration * deltaTime);
                else character->setXVelocity(max(character->getVelocity().x, max_walk_velocity));
                if (character->isJumping() == false) {
                    if (character->velocity.x >= max_run_velocity && IsKeyDown(KEY_LEFT_SHIFT)) {
                        character->setAnimation(character->runRight);
                    }
                    else character->setAnimation(character->walkRight);
                }

            }
        }
        else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
            if (character->velocity.x > 0) {
                if (character->isJumping() == false) character->setAnimation(character->stopRight);
                character->setXVelocity(character->getVelocity().x - deceleration * deltaTime);
                if (character->velocity.x < 0) character->setXVelocity(-max_walk_velocity);
            }
            else {
                if (IsKeyDown(KEY_LEFT_SHIFT)) character->setXVelocity(character->getVelocity().x - acceleration * deltaTime);
                else character->setXVelocity(min(character->getVelocity().x, -max_walk_velocity));
                if (character->isJumping() == false) {
                    if (fabs(character->velocity.x) >= max_run_velocity && IsKeyDown(KEY_LEFT_SHIFT)) {
                        character->setAnimation(character->runLeft);
                    }
                    else character->setAnimation(character->walkLeft);
                }
            }

        }
        else {
            if (character->velocity.x > 0) {
                character->setXVelocity(character->getVelocity().x - deceleration * deltaTime);
                if (character->velocity.x < 0) character->setXVelocity(0.f);
                if (character->isJumping() == false) character->setAnimation(character->stopRight);
            }
            else if (character->velocity.x < 0) {
                character->setXVelocity(character->getVelocity().x + deceleration * deltaTime);
                if (character->velocity.x > 0) character->setXVelocity(0.f);
                if (character->isJumping() == false) character->setAnimation(character->stopLeft);
            }
        }

        if (character->velocity.x > 0) character->orientation = true;
        else if (character->velocity.x < 0) character->orientation = false;


        if (IsKeyPressed(KEY_SPACE) && character->isJumping() == false) {
            character->setYVelocity(-jump_velocity);
            character->jumping = true;
            RESOURCE_MANAGER.playSound("jump.wav");
        }
        else if (character->isJumping()) {
            character->setYVelocity(character->getVelocity().y + gravity * deltaTime);

            //if (character->onGround()) {
            //    character->setPosition(Vector2(character->getPosition().x, 800.f - character->getSize().y));
            //    character->setYVelocity(0.f);
            //    character->jumping = false;  
            //}
        }

        if (IsKeyUp(KEY_LEFT_SHIFT) && fabs(character->velocity.x) > max_walk_velocity) {
            if (character->velocity.x > 0) {
                character->setXVelocity(max(character->getVelocity().x - acceleration * deltaTime, max_walk_velocity)); 
            }
            else if (character->velocity.x < 0) {
                character->setXVelocity(min(character->getVelocity().x + acceleration * deltaTime, -max_walk_velocity));
            }
        }
        else if (IsKeyDown(KEY_LEFT_SHIFT) && fabs(character->velocity.x) > max_run_velocity) {
            character->setXVelocity((character->velocity.x > 0) ? max_run_velocity : -max_run_velocity);
        }
            
            
        if (character->isJumping()) {
            if (fabs(character->getVelocity().x) >= max_run_velocity) {
                if (character->orientation) character->setAnimation(character->flyRight);
                else character->setAnimation(character->flyLeft);
            }
            else {
                if (character->orientation) character->setAnimation(character->jumpRight);
                else character->setAnimation(character->jumpLeft);
            }
        }

        if (character->isIdle()) {
            if (character->orientation) character->setAnimation(character->idleRight);
            else character->setAnimation(character->idleLeft);
        }

            
        if (!character->isJumping() && fabs(character->getVelocity().x) >= max_run_velocity) {
            if (!RESOURCE_MANAGER.isSoundPlaying("pmeter.wav")) RESOURCE_MANAGER.playSound("pmeter.wav");
        }
        else RESOURCE_MANAGER.stopSound("pmeter.wav");

        character->setPosition(Vector2(character->getPosition().x + character->velocity.x * deltaTime, character->getPosition().y + character->velocity.y * deltaTime));
    }

    STATE getState() const override {
        return NORMAL;
    }
};