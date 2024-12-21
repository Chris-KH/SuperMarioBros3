#include "../include/Character.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"
#include"../include/Item.h"
#include"../include/Mushroom.h"
#include"../include/Flower.h"
#include"../include/Star.h"
#include"../include/Coin.h"
#include"../include/Enemy.h"
#include"../include/Shell.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    lostLife = false;
    invicible = 0;
    sitting = false;
    state = nullptr;

    idleLeft = nullptr;
	walkLeft = nullptr;
	runLeft = nullptr;
	stopLeft = nullptr;
	jumpLeft = nullptr;
	fallLeft = nullptr;
	flyLeft = nullptr;
	sitLeft = nullptr;
	holdLeft = nullptr;
	throwLeft = nullptr;
	kickLeft = nullptr;

	idleRight = nullptr;
	walkRight = nullptr;
	runRight = nullptr;
	stopRight = nullptr;
	jumpRight = nullptr;
	fallRight = nullptr;
	flyRight = nullptr;
	sitRight = nullptr;
	holdRight = nullptr;
	throwRight = nullptr;
	kickRight = nullptr;
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
    lostLife = false;
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

void Character::transform(STATE type) {
    Character* character = state->getCharacter();
    free(state);
    if (type == NORMAL) {
        state = new NormalState(character);
    }
    else if (type == SUPER) {
        state = new SuperState(character);
    }
    else if (type == FIRE) {
        state = new FireState(character);
    }
    else if (type == STAR) {
        state = new StarmanState(character);
    }
    else if (type == SUPERSTARMAN) {
        state = new SuperStarmanState(character);
    }
    else if (type == FIRESTARMAN) {
        state = new FireStarmanState(character);
    }
    else state = nullptr;
}

void Character::collisionWithItem(const Item* item) {
    if (item->getItemType() == MUSHROOM) {
		const Mushroom* mushroom = dynamic_cast<const Mushroom*>(item);
        if (mushroom->getMushroomType() == MUSHROOM_SUPER) {
            scores += mushroom->POINT;
			if (getState() == NORMAL) {
				transform(SUPER);
				phase = TRANSFORM_PHASE;
			}
			RESOURCE_MANAGER.playSound("powerup.wav");
        }
        else if (mushroom->getMushroomType() == MUSHROOM_1UP) {
            lives++;
            RESOURCE_MANAGER.playSound("1up.wav");
        }
    }
    else if (item->getItemType() == FLOWER) {
		const Flower* flower = dynamic_cast<const Flower*>(item);
        if (flower->getFlowerType() == FIRE_FLOWER) {
            scores += flower->POINT;
            if (getState() == NORMAL) {
                transform(FIRE);
				phase = TRANSFORM_PHASE;
            }
            RESOURCE_MANAGER.playSound("powerup.wav");
        }
    }
	else if (item->getItemType() == STAR) {
		const Star* star = dynamic_cast<const Star*>(item);
        if (star->getStarType() == YELLOW_STAR) {
            if (getState() == NORMAL) {
                transform(STARMAN);
                phase = TRANSFORM_PHASE;
            }
            else if (getState() == SUPER) {
                transform(SUPERSTARMAN);
                phase = TRANSFORM_PHASE;
            }
            else if (getState() == FIRE) {
                transform(FIRESTARMAN);
                phase = TRANSFORM_PHASE;
            }
			scores += star->POINT;
			RESOURCE_MANAGER.playSound("powerup.wav");
        }
	}
	else if (item->getItemType() == COIN) {
		const Coin* coin = dynamic_cast<const Coin*>(item);
		if (coin->getCoinType() == STATIC_COIN) {
			coins++;
			scores += coin->POINT;
			RESOURCE_MANAGER.playSound("coin.wav");
		}
	}
	else {
		//Do nothing
	}
};

void Character::collisionWithEnemy(const Enemy* enemy) {
    if (enemy->getEnemyType() != SHELL) {
        scores += 100.f;
        setYVelocity(-getVelocity().y);
        setJumping(true);
    }
}