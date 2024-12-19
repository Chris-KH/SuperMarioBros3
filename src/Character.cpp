#include "../include/Character.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
   
    reset();
};

Character::~Character() {
    free(state);
    state = nullptr;
    INPUT_MANAGER.removeListener(*this);
}

EntityType Character::getType() const { return EntityType::CHARACTER; }

void Character::reset() {
    orientation = RIGHT;
    jumping = false;
    dead = false;
    invicible = 0;
    sitting = false;
}

STATE Character::getState() const {
    return state->getState();
}

void Character::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    currentAnimation->render(getPosition());
}

void Character::setState() {
    state->setState(this);
}

void Character::setAnimation(Animation* animation) {
    if (currentAnimation != nullptr && currentAnimation != animation) currentAnimation->reset();
    currentAnimation = animation;
    if (currentAnimation == nullptr) return;

    float diffHeight = this->getSize().y - currentAnimation->getSize().y;

    this->setYPosition(this->getPosition().y + diffHeight);
    this->setSize(currentAnimation->getSize());
};


bool Character::isDead() const { return dead; }

bool Character::isInvicible() const { return invicible > 1e-9; }

bool Character::isIdle() const {
    return (velocity.x == 0.f && velocity.y == 0.f && !isJumping());
}

int Character::getLives() const { return lives; }

int Character::getCoins() const { return coins; }

int Character::getScores() const { return scores; }