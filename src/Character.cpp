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
    sitting = false;
}

CharacterState::STATE Character::getState() const {
    return state->getState();
}

void Character::draw(float deltaTime) {
    Vector2 vector2 = {getPosition().x + velocity.x * deltaTime, getPosition().y + velocity.y * deltaTime};
    setPosition(vector2);
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