#include "../include/Character.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarState.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
   
    reset();
};

Character::~Character() {
    delete state;
    INPUT_MANAGER.removeListener(*this);
}

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

void Character::draw() {
    currentAnimation->render(getPosition());
}

void Character::setState() {
    state->setState(this);
}

bool Character::isJumping() const { return jumping; }

bool Character::isDead() const { return dead; }

bool Character::isInvicible() const { return invicible > 1e-9; }

bool Character::isIdle() const {
    return (velocity.x == 0.f && velocity.y == 0.f && !isJumping());
}

int Character::getLives() const { return lives; }

int Character::getCoins() const { return coins; }

int Character::getScores() const { return scores; }