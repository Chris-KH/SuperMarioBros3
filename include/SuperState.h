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
            character->walkLeft = RESOURCE_MANAGER.getAnimation("supermario_walk_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("supermario_run_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("supermario_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("supermario_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("supermario_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("supermario_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("supermario_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("supermario_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("supermario_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("supermario_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("supermario_fall_right");
        }
        else if (dynamic_cast<Luigi*>(character) != nullptr) {
            character->idleLeft = RESOURCE_MANAGER.getAnimation("superluigi_idle_left");
            character->walkLeft = RESOURCE_MANAGER.getAnimation("superluigi_walk_left");
            character->runLeft = RESOURCE_MANAGER.getAnimation("superluigi_run_left");
            character->stopLeft = RESOURCE_MANAGER.getAnimation("superluigi_stop_left");
            character->jumpLeft = RESOURCE_MANAGER.getAnimation("superluigi_jump_left");
            character->fallLeft = RESOURCE_MANAGER.getAnimation("superluigi_fall_left");

            character->idleRight = RESOURCE_MANAGER.getAnimation("superluigi_idle_right");
            character->walkRight = RESOURCE_MANAGER.getAnimation("superluigi_walk_right");
            character->runRight = RESOURCE_MANAGER.getAnimation("superluigi_run_right");
            character->stopRight = RESOURCE_MANAGER.getAnimation("superluigi_stop_right");
            character->jumpRight = RESOURCE_MANAGER.getAnimation("superluigi_jump_right");
            character->fallRight = RESOURCE_MANAGER.getAnimation("superluigi_fall_right");
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

                //if (mario->onGround()) {
                //    mario->setPosition(Vector2(mario->getPosition().x, 800.f - mario->getSize().y));
                //    mario->setYVelocity(0.f);
                //    mario->jumping = false;
                //}
            }

            // Giới hạn vận tốc (max speed)
            if (fabs(mario->velocity.x) > mario->MAX_RUN_VELOCITY) {
                mario->setXVelocity((mario->velocity.x > 0) ? mario->MAX_RUN_VELOCITY : -mario->MAX_RUN_VELOCITY);
            }

            if (mario->isJumping()) {
                if (mario->velocity.y < 0) {
                    if (mario->orientation) mario->setAnimation(mario->jumpRight);
                    else mario->setAnimation(mario->jumpLeft);
                }
                else if (mario->velocity.y >= 0) {
                    if (mario->orientation) mario->setAnimation(mario->fallRight);
                    else mario->setAnimation(mario->fallLeft);
                }
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

          /*      if (luigi->onGround()) {
                    luigi->setPosition(Vector2(luigi->getPosition().x, 800.f - luigi->getSize().y));
                    luigi->setYVelocity(0.f);
                    luigi->jumping = false;
                }*/
            }

            // Giới hạn vận tốc (max speed)
            if (fabs(luigi->velocity.x) > luigi->MAX_RUN_VELOCITY) {
                luigi->setXVelocity((luigi->velocity.x > 0) ? luigi->MAX_RUN_VELOCITY : -luigi->MAX_RUN_VELOCITY);
            }

            
            if (luigi->isJumping()) {
                if (luigi->velocity.y < 0) {
                    if (luigi->orientation) luigi->setAnimation(luigi->jumpRight);
                    else luigi->setAnimation(luigi->jumpLeft);
                }
                else if (luigi->velocity.y >= 0) {
                    if (luigi->orientation) luigi->setAnimation(luigi->fallRight);
                    else luigi->setAnimation(luigi->fallLeft);
                }
            }

            if (luigi->isIdle()) {
                if (luigi->orientation) luigi->setAnimation(luigi->idleRight);
                else luigi->setAnimation(luigi->idleLeft);
            }

            luigi->setPosition(Vector2(luigi->getPosition().x + luigi->velocity.x * deltaTime, luigi->getPosition().y + luigi->velocity.y * deltaTime));
        }
    }

	STATE getState() const override {
		return SUPER;
	}
};