#include "../include/SuperStarmanState.h"

SuperStarmanState::SuperStarmanState(Character* character) : CharacterState(character) {
    setAnimation();
}

void SuperStarmanState::setAnimation() {
    Character* character = getCharacter();

    if (character == nullptr) {
        return; // Avoid dereferencing a null pointer
    }

    if (character->getCharacterType() == MARIO) {
        character->idleLeft = RESOURCE_MANAGER.getAnimation("superstarmario_idle_left");
        character->walkLeft = RESOURCE_MANAGER.getAnimation("superstarmario_walk_left");
        character->runLeft = RESOURCE_MANAGER.getAnimation("superstarmario_run_left");
        character->stopLeft = RESOURCE_MANAGER.getAnimation("superstarmario_stop_left");
        character->jumpLeft = RESOURCE_MANAGER.getAnimation("superstarmario_jump_left");
        character->fallLeft = RESOURCE_MANAGER.getAnimation("superstarmario_fall_left");
        character->flyLeft = RESOURCE_MANAGER.getAnimation("superstarmario_fly_left");
        character->sitLeft = RESOURCE_MANAGER.getAnimation("superstarmario_sit_left");
        character->holdLeft = RESOURCE_MANAGER.getAnimation("superstarmario_hold_left");

        character->idleRight = RESOURCE_MANAGER.getAnimation("superstarmario_idle_right");
        character->walkRight = RESOURCE_MANAGER.getAnimation("superstarmario_walk_right");
        character->runRight = RESOURCE_MANAGER.getAnimation("superstarmario_run_right");
        character->stopRight = RESOURCE_MANAGER.getAnimation("superstarmario_stop_right");
        character->jumpRight = RESOURCE_MANAGER.getAnimation("superstarmario_jump_right");
        character->fallRight = RESOURCE_MANAGER.getAnimation("superstarmario_fall_right");
        character->flyRight = RESOURCE_MANAGER.getAnimation("superstarmario_fly_right");
        character->sitRight = RESOURCE_MANAGER.getAnimation("superstarmario_sit_right");
        character->holdRight = RESOURCE_MANAGER.getAnimation("superstarmario_hold_right");
    }
    else if (character->getCharacterType() == LUIGI) {
        character->idleLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_idle_left");
        character->walkLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_walk_left");
        character->runLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_run_left");
        character->stopLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_stop_left");
        character->jumpLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_jump_left");
        character->fallLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_fall_left");
        character->flyLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_fly_left");
        character->sitLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_sit_left");
        character->holdLeft = RESOURCE_MANAGER.getAnimation("superstarluigi_hold_left");

        character->idleRight = RESOURCE_MANAGER.getAnimation("superstarluigi_idle_right");
        character->walkRight = RESOURCE_MANAGER.getAnimation("superstarluigi_walk_right");
        character->runRight = RESOURCE_MANAGER.getAnimation("superstarluigi_run_right");
        character->stopRight = RESOURCE_MANAGER.getAnimation("superstarluigi_stop_right");
        character->jumpRight = RESOURCE_MANAGER.getAnimation("superstarluigi_jump_right");
        character->fallRight = RESOURCE_MANAGER.getAnimation("superstarluigi_fall_right");
        character->flyRight = RESOURCE_MANAGER.getAnimation("superstarluigi_fly_right");
        character->sitRight = RESOURCE_MANAGER.getAnimation("superstarluigi_sit_right");
        character->holdRight = RESOURCE_MANAGER.getAnimation("superstarluigi_hold_right");
    }

    character->kickLeft = nullptr;
    character->kickRight = nullptr;
    character->throwLeft = nullptr;
    character->throwRight = nullptr;
}

void SuperStarmanState::update(float deltaTime) {
    Character* character = getCharacter();

    if (character == nullptr) {
        return; // Avoid dereferencing a null pointer
    }

    float starmanBoost = 1.2f;

    float skid_deceleration, deceleration, acceleration, gravity, jump_velocity, max_run_velocity, max_walk_velocity;
    gravity = character->GRAVITY;
    if (dynamic_cast<Mario*>(character) != nullptr) {
        Mario* mario = dynamic_cast<Mario*>(character);
        skid_deceleration = mario->GROUND_SKID_DECELERATION;
        deceleration = mario->GROUND_DECCELERATION;
        acceleration = mario->GROUND_ACCELERATION;
        jump_velocity = mario->JUMP_VELOCITY * starmanBoost;
        max_run_velocity = mario->MAX_RUN_VELOCITY * starmanBoost;
        max_walk_velocity = mario->MAX_WALK_VELOCITY * starmanBoost;
    }
    else if (dynamic_cast<Luigi*>(character) != nullptr) {
        Luigi* luigi = dynamic_cast<Luigi*>(character);
        skid_deceleration = luigi->GROUND_SKID_DECELERATION;
        deceleration = luigi->GROUND_DECCELERATION;
        acceleration = luigi->GROUND_ACCELERATION;
        jump_velocity = luigi->JUMP_VELOCITY * starmanBoost;
        max_run_velocity = luigi->MAX_RUN_VELOCITY * starmanBoost;
        max_walk_velocity = luigi->MAX_WALK_VELOCITY * starmanBoost;
    }

    //Logic update
    character->setSitting(IsKeyDown(KEY_S) && character->isHolding() == false);

    if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
        character->setSitting(false);
        if (character->velocity.x < 0) {
            if (character->isJumping() == false && character->isHolding() == false && character->isSitting() == false) {
                character->setAnimation(character->stopLeft);
                RESOURCE_MANAGER.playSound("skid.wav");
            }
            character->setXVelocity(character->getVelocity().x + skid_deceleration * deltaTime);
            if (character->velocity.x > 0) character->setXVelocity(0.f);
        }
        else {
            character->setXVelocity(character->getVelocity().x + acceleration * deltaTime);
            if (character->isJumping() == false && character->isHolding() == false) {
                if (character->velocity.x >= max_run_velocity && IsKeyDown(KEY_LEFT_SHIFT)) {
                    character->setAnimation(character->runRight);
                }
                else character->setAnimation(character->walkRight);
            }

        }
    }
    else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
        character->setSitting(false);
        if (character->velocity.x > 0) {
            if (character->isJumping() == false && character->isHolding() == false && character->isSitting() == false) {
                character->setAnimation(character->stopRight);
                RESOURCE_MANAGER.playSound("skid.wav");
            }
            character->setXVelocity(character->getVelocity().x - skid_deceleration * deltaTime);
            if (character->velocity.x < 0) character->setXVelocity(0.f);
        }
        else {
            character->setXVelocity(character->getVelocity().x - acceleration * deltaTime);
            if (character->isJumping() == false && character->isHolding() == false) {
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
            if (character->isJumping() == false && character->isHolding() == false && character->isSitting() == false) character->setAnimation(character->walkRight);
        }
        else if (character->velocity.x < 0) {
            character->setXVelocity(character->getVelocity().x + deceleration * deltaTime);
            if (character->velocity.x > 0) character->setXVelocity(0.f);
            if (character->isJumping() == false && character->isHolding() == false && character->isSitting() == false) character->setAnimation(character->walkLeft);
        }
    }

    if (character->velocity.x > 0.f) character->orientation = RIGHT;
    else if (character->velocity.x < 0.f) character->orientation = LEFT;

    if (character->isHolding()) {
        character->setHoldAnimation();
    }

    if (IsKeyPressed(KEY_SPACE) && character->isJumping() == false) {
        character->setYVelocity(-jump_velocity);
        character->jumping = true;
        RESOURCE_MANAGER.playSound("jump.wav");
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

    if (character->isIdle() && character->isSitting() == false && character->isHolding() == false) {
        character->setIdleAnimation();
    }


    if (character->isJumping()) {
        character->setSitting(false);
        if (fabs(character->getVelocity().x) >= max_run_velocity && character->isHolding() == false) {
            character->setFlyAnimation();
        }
        else {
            if (character->velocity.y < 0) {
                if (character->isHolding() == false) character->setJumpAnimation();
                if (IsKeyReleased(KEY_SPACE)) character->setYVelocity(character->getVelocity().y * 0.5f);
            }
            if (character->velocity.y >= 0) {
                if (character->isHolding() == false) character->setFallAnimation();
            }
        }
    }

    character->setYVelocity(character->getVelocity().y + gravity * deltaTime);

    if (character->isSitting() && character->isHolding() == false) {
        character->setSitAnimation();
    }

    if (!character->isJumping() && fabs(character->getVelocity().x) >= max_run_velocity) {
        if (!RESOURCE_MANAGER.isSoundPlaying("pmeter.wav")) RESOURCE_MANAGER.playSound("pmeter.wav");
    }
    else RESOURCE_MANAGER.stopSound("pmeter.wav");
}

STATE SuperStarmanState::getState() const {
    return SUPERSTARMAN;
}