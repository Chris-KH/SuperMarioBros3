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
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("mario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("mario_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("mario_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("mario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("mario_jump_right");
            character->fallRight = nullptr;
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("luigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("luigi_walk_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("luigi_run_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("luigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("luigi_jump_left");
            character->fallLeft = nullptr;

            character->idleRight = RESOURCE_MANAGER.getAnimation("luigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("luigi_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("luigi_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("luigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("luigi_jump_right");
            character->fallRight = nullptr;
        }
    }

    void update(Character* character, float deltaTime) override {
        if (character == nullptr) {
            return; // Avoid dereferencing a null pointer
        }

        if (dynamic_cast<Mario*>(character) != nullptr) {
            Mario* mario = dynamic_cast<Mario*>(character);
            
            const float deceleration = mario->GROUND_DEACCELERATION; 
            const float acceleration = mario->GROUND_ACCELERATION;
            const float gravity = mario->GRAVITY;

            /*mario->setPosition(Vector2(mario->getPosition().x + mario->velocity.x * deltaTime, mario->getPosition().y + mario->velocity.y * deltaTime));
            mario->draw();*/
            
            if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) { 
                if (mario->velocity.x < 0) {  
                    if (mario->isJumping() == false) mario->setAnimation(mario->stopLeft);
                    mario->setXVelocity(mario->getVelocity().x + deceleration * deltaTime);
                    if (mario->velocity.x > 0) mario->setXVelocity(0.f);
                }
                else {
                    mario->setXVelocity(mario->getVelocity().x + acceleration * deltaTime);
                    if (mario->isJumping() == false) {
                        if (mario->velocity.x >= mario->MAX_RUN_VELOCITY) {
                            mario->setAnimation(mario->runRight);
                        }
                        else mario->setAnimation(mario->walkRight);
                    }
                    
                }
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {  
                if (mario->velocity.x > 0) {
                    if (mario->isJumping() == false) mario->setAnimation(mario->stopRight);
                    mario->setXVelocity(mario->getVelocity().x - deceleration * deltaTime);
                    if (mario->velocity.x < 0) mario->setXVelocity(0.f);
                }
                else {
                    mario->setXVelocity(mario->getVelocity().x - acceleration * deltaTime);
                    if (mario->isJumping() == false) {
                        if (abs(mario->velocity.x) >= mario->MAX_RUN_VELOCITY) {
                            mario->setAnimation(mario->runLeft);
                        }
                        else mario->setAnimation(mario->walkLeft);
                    }
                }

            }
            else { 
                if (mario->velocity.x > 0) {
                    mario->setXVelocity(mario->getVelocity().x - deceleration * deltaTime);
                    if (mario->velocity.x < 0) mario->setXVelocity(0.f);
                    if (mario->isJumping() == false) mario->setAnimation(mario->stopRight);
                }
                else if (mario->velocity.x < 0) {
                    mario->setXVelocity(mario->getVelocity().x + deceleration * deltaTime);
                    if (mario->velocity.x > 0) mario->setXVelocity(0.f);
                    if (mario->isJumping() == false) mario->setAnimation(mario->stopLeft);
                }
            }

            if (mario->velocity.x > 0) mario->orientation = true;
            else if (mario->velocity.x < 0) mario->orientation = false;


            if (IsKeyDown(KEY_SPACE) && mario->isJumping() == false) {
                mario->setYVelocity(-mario->JUMP_VELOCITY);
                if (mario->velocity.x > 0) mario->setAnimation(mario->jumpRight);
                else if (mario->velocity.x < 0) mario->setAnimation(mario->jumpLeft);
                mario->jumping = true;
                RESOURCE_MANAGER.playSound("jump.wav");
            }
            else if (mario->isJumping()) {
                mario->setYVelocity(mario->getVelocity().y + gravity * deltaTime);
                
                if (mario->onGround()) {
                    mario->setPosition(Vector2(mario->getPosition().x, 800.f - mario->getSize().y));
                    mario->setYVelocity(0.f);
                    mario->jumping = false;  
                }
            }

            // Giới hạn vận tốc (max speed)
            if (fabs(mario->velocity.x) > mario->MAX_RUN_VELOCITY) {
                mario->setXVelocity((mario->velocity.x > 0) ? mario->MAX_RUN_VELOCITY : -mario->MAX_RUN_VELOCITY);
            }

            if (mario->isJumping()) {
                if (mario->orientation) mario->setAnimation(mario->jumpRight);
                else mario->setAnimation(mario->jumpLeft);
            }

            if (mario->isIdle()) {
                if (mario->orientation) mario->setAnimation(mario->idleRight);
                else mario->setAnimation(mario->idleLeft);
            }

            mario->setPosition(Vector2(mario->getPosition().x + mario->velocity.x * deltaTime, mario->getPosition().y + mario->velocity.y * deltaTime));

        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            Luigi* luigi = dynamic_cast<Luigi*>(character);

            const float deceleration = luigi->GROUND_DEACCELERATION;
            const float acceleration = luigi->GROUND_ACCELERATION;
            const float gravity = luigi->GRAVITY;

            /*luigi->setPosition(Vector2(luigi->getPosition().x + luigi->velocity.x * deltaTime, luigi->getPosition().y + luigi->velocity.y * deltaTime));
            luigi->draw();*/

            if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
                if (luigi->velocity.x < 0) {
                    if (luigi->isJumping() == false) luigi->setAnimation(luigi->stopLeft);
                    luigi->setXVelocity(luigi->getVelocity().x + deceleration * deltaTime);
                    if (luigi->velocity.x > 0) luigi->setXVelocity(0.f);
                }
                else {
                    luigi->setXVelocity(luigi->getVelocity().x + acceleration * deltaTime);
                    if (luigi->isJumping() == false) {
                        if (luigi->velocity.x >= luigi->MAX_RUN_VELOCITY) {
                            luigi->setAnimation(luigi->runRight);
                        }
                        else luigi->setAnimation(luigi->walkRight);
                    }

                }
            }
            else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
                if (luigi->velocity.x > 0) {
                    if (luigi->isJumping() == false) luigi->setAnimation(luigi->stopRight);
                    luigi->setXVelocity(luigi->getVelocity().x - deceleration * deltaTime);
                    if (luigi->velocity.x < 0) luigi->setXVelocity(0.f);
                }
                else {
                    luigi->setXVelocity(luigi->getVelocity().x - acceleration * deltaTime);
                    if (luigi->isJumping() == false) {
                        if (abs(luigi->velocity.x) >= luigi->MAX_RUN_VELOCITY) {
                            luigi->setAnimation(luigi->runLeft);
                        }
                        else luigi->setAnimation(luigi->walkLeft);
                    }
                }

            }
            else {
                if (luigi->velocity.x > 0) {
                    luigi->setXVelocity(luigi->getVelocity().x - deceleration * deltaTime);
                    if (luigi->velocity.x < 0) luigi->setXVelocity(0.f);
                    if (luigi->isJumping() == false) luigi->setAnimation(luigi->stopRight);
                }
                else if (luigi->velocity.x < 0) {
                    luigi->setXVelocity(luigi->getVelocity().x + deceleration * deltaTime);
                    if (luigi->velocity.x > 0) luigi->setXVelocity(0.f);
                    if (luigi->isJumping() == false) luigi->setAnimation(luigi->stopLeft);
                }
            }

            if (luigi->velocity.x > 0) luigi->orientation = true;
            else if (luigi->velocity.x < 0) luigi->orientation = false;


            if (IsKeyDown(KEY_SPACE) && luigi->isJumping() == false) {
                luigi->setYVelocity(-luigi->JUMP_VELOCITY);
                if (luigi->velocity.x > 0) luigi->setAnimation(luigi->jumpRight);
                else if (luigi->velocity.x < 0) luigi->setAnimation(luigi->jumpLeft);
                luigi->jumping = true;
                RESOURCE_MANAGER.playSound("jump.wav");
            }
            else if (luigi->isJumping()) {
                luigi->setYVelocity(luigi->getVelocity().y + gravity * deltaTime);

                if (luigi->onGround()) {
                    luigi->setPosition(Vector2(luigi->getPosition().x, 800.f - luigi->getSize().y));
                    luigi->setYVelocity(0.f);
                    luigi->jumping = false;
                }
            }

            // Giới hạn vận tốc (max speed)
            if (fabs(luigi->velocity.x) > luigi->MAX_RUN_VELOCITY) {
                luigi->setXVelocity((luigi->velocity.x > 0) ? luigi->MAX_RUN_VELOCITY : -luigi->MAX_RUN_VELOCITY);
            }

            if (luigi->isJumping()) {
                if (luigi->orientation) luigi->setAnimation(luigi->jumpRight);
                else luigi->setAnimation(luigi->jumpLeft);
            }

            if (luigi->isIdle()) {
                if (luigi->orientation) luigi->setAnimation(luigi->idleRight);
                else luigi->setAnimation(luigi->idleLeft);
            }

            luigi->setPosition(Vector2(luigi->getPosition().x + luigi->velocity.x * deltaTime, luigi->getPosition().y + luigi->velocity.y * deltaTime));
        }
    }

    STATE getState() const override {
        return NORMAL;
    }
};