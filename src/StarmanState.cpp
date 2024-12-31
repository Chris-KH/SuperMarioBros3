#include "../include/StarmanState.h"

StarmanState::StarmanState(Character* character) : CharacterState(character) {
    setAnimation();
}

void StarmanState::setAnimation() {
    Character* character = getCharacter();

    if (character == nullptr) {
        return; // Avoid dereferencing a null pointer
    }

    if (character->getCharacterType() == MARIO) {
        character->idleLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_idle_left");
        character->walkLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_walk_left");
        character->runLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_run_left");
        character->stopLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_stop_left");
        character->jumpLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_jump_left");
        character->flyLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_fly_left");
        character->holdLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_hold_left");

        character->idleRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_idle_right");
        character->walkRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_walk_right");
        character->runRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_run_right");
        character->stopRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_stop_right");
        character->jumpRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_jump_right");
        character->flyRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_fly_right");
        character->holdRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/mario1.txt/starmario_hold_right");
    }
    else if (character->getCharacterType() == LUIGI) {
        character->idleLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_idle_left");
        character->walkLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_walk_left");
        character->runLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_run_left");
        character->stopLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_stop_left");
        character->jumpLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_jump_left");
        character->flyLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_fly_left");
        character->holdLeft = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_hold_left");

        character->idleRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_idle_right");
        character->walkRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_walk_right");
        character->runRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_run_right");
        character->stopRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_stop_right");
        character->jumpRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_jump_right");
        character->flyRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_fly_right");
        character->holdRight = RESOURCE_MANAGER.getAnimation("../../assets/Animation/luigi1.txt/starluigi_hold_right");
    }

    character->kickLeft = nullptr;
    character->kickRight = nullptr;
    character->fallLeft = nullptr;
    character->fallRight = nullptr;
    character->sitLeft = nullptr;
    character->sitRight = nullptr;
    character->throwLeft = nullptr;
    character->throwRight = nullptr;
}

void StarmanState::update(float deltaTime) {
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
    if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
        if (character->velocity.x < 0) {
            if (character->isJumping() == false && character->isHolding() == false) {
                character->setAnimation(character->stopLeft);
                RESOURCE_MANAGER.playSound("../../assets/Sound/skid.wav");
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
        if (character->velocity.x > 0) {
            if (character->isJumping() == false && character->isHolding() == false) {
                character->setAnimation(character->stopRight);
                RESOURCE_MANAGER.playSound("../../assets/Sound/skid.wav");
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
            if (character->isJumping() == false && character->isHolding() == false) character->setAnimation(character->walkRight);
        }
        else if (character->velocity.x < 0) {
            character->setXVelocity(character->getVelocity().x + deceleration * deltaTime);
            if (character->velocity.x > 0) character->setXVelocity(0.f);
            if (character->isJumping() == false && character->isHolding() == false) character->setAnimation(character->walkLeft);
        }
    }

    if (character->velocity.x > 0) character->orientation = RIGHT;
    else if (character->velocity.x < 0) character->orientation = LEFT;

    if (character->isHolding()) {
        character->setHoldAnimation();
    }

    if (IsKeyPressed(KEY_SPACE) && character->isJumping() == false) {
        character->setYVelocity(-jump_velocity);
        character->jumping = true;
        RESOURCE_MANAGER.playSound("../../assets/Sound/jump.wav");
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

    if (character->isIdle() && character->isHolding() == false) {
        character->setIdleAnimation();
    }


    if (character->isJumping()) {
        if (fabs(character->getVelocity().x) >= max_run_velocity && character->isHolding() == false) {
            character->setFlyAnimation();
        }
        else {
            if (character->isHolding() == false) character->setJumpAnimation();
            if (character->velocity.y < 0) {
                if (IsKeyReleased(KEY_SPACE)) character->setYVelocity(character->getVelocity().y * 0.5f);
            }
        }
    }

    character->setYVelocity(character->getVelocity().y + gravity * deltaTime);

    if (!character->isJumping() && fabs(character->getVelocity().x) >= max_run_velocity) {
        if (!RESOURCE_MANAGER.isSoundPlaying("../../assets/Sound/pmeter.wav")) RESOURCE_MANAGER.playSound("../../assets/Sound/pmeter.wav");
    }
    else RESOURCE_MANAGER.stopSound("../../assets/Sound/pmeter.wav");
}

STATE StarmanState::getState() const {
    return STARMAN;
}