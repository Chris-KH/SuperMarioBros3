#include "../include/Character.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    dead = false;
    invicible = 0;
    sitting = false;
};

Character::~Character() {
    free(state);
    state = nullptr;
    INPUT_MANAGER.removeListener(*this);
}

EntityType Character::getType() const { return EntityType::CHARACTER; }

void Character::reset() {
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
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
	if (isDead()) return;

    if (currentAnimation == nullptr) return;
    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    updateTime(deltaTime);
    currentAnimation->update(deltaTime);
    currentAnimation->render(getPosition());
}

void Character::setPhase(Phase phase) {
	this->phase = phase;
}

const Character::Phase& Character::getPhase() const {
	return phase;
}

void Character::setState() {
    state->setState(this);
}

bool Character::isDead() const { return dead; }

bool Character::isInvicible() const { return invicible > 1e-9; }

bool Character::isIdle() const {
    return (velocity.x == 0.f && velocity.y == 0.f && !isJumping());
}

int Character::getLives() const { return lives; }

void Character::setLives(int lives)
{
    this->lives = lives;
}
int Character::getCoins() const { return coins; }

void Character::setCoins(int coins)
{
    this->coins = coins;
}

int Character::getScores() const { return scores; }

void Character::setScores(int score)
{
    this->scores = score;
}

void Character::setIdleAnimation() {
    if (orientation == RIGHT) setAnimation(idleRight);
    else if (orientation == LEFT) setAnimation(idleLeft);
}

void Character::setWalkAnimation() {
    if (orientation == RIGHT) setAnimation(walkRight);
    else if (orientation == LEFT) setAnimation(walkLeft);
}

void Character::setRunAnimation() {
    if (orientation == RIGHT) setAnimation(runRight);
    else if (orientation == LEFT) setAnimation(runLeft);
}

void Character::setJumpAnimation() {
    if (orientation == RIGHT) setAnimation(jumpRight);
    else if (orientation == LEFT) setAnimation(jumpLeft);
}

void Character::setStopAnimation() {
    if (orientation == RIGHT) setAnimation(stopRight);
    else if (orientation == LEFT) setAnimation(stopLeft);
}

void Character::setFallAnimation() {
    if (orientation == RIGHT) setAnimation(fallRight);
    else if (orientation == LEFT) setAnimation(fallLeft);
}

void Character::setSitAnimation() {
    if (orientation == RIGHT) setAnimation(sitRight);
    else if (orientation == LEFT) setAnimation(sitLeft);
}

void Character::setFlyAnimation() {
    if (orientation == RIGHT) setAnimation(flyRight);
    else if (orientation == LEFT) setAnimation(flyLeft);
}

void Character::setInvicible(bool invicible) {
    this->invicible = invicible;
}

void Character::setSitting(bool sitting) {
    this->sitting = sitting;
}