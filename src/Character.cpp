#include "../include/Character.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
    state = new NormalState;

    reset();
};

EntityType Character::getType() const { return EntityType::CHACRACTER; }

void Character::reset() {
    orientation = true;
    jumping = false;
    dead = false;
    invicible = 0;
}

CharacterState::STATE Character::getState() const {
    return state->getState();
}

bool Character::isJumping() const { return jumping; }

bool Character::isDead() const { return dead; }

bool Character::isInvicible() const { return invicible > 1e-9; }

int Character::getLives() const { return lives; }

int Character::getCoins() const { return coins; }

int Character::getScores() const { return scores; }