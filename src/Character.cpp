#include"../include/Character.h"
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
#include"../include/Effect.h"
#include"../include/TextEffect.h"
#include"../include/GameEngine.h"

Character::Character(Vector2 pos, Vector2 size, Color col) : Sprite(pos, size, col)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    holding = false;
    lostLife = false;
    invicibleTime = 0.f;
    sitting = false;
    state = nullptr;
    holdShell = nullptr;
    countThrowTime = 0.f;

    lastState = NORMAL;
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
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    holding = false;
    lostLife = false;
    invicibleTime = 0.f;
    sitting = false;
    state = nullptr;
}

STATE Character::getState() const {
    return state->getState();
}

void Character::draw(float deltaTime) {
	if (isDead()) return;


    if (isHolding() && holdShell) {
        if (holdShell->isDead() == false) {
            holdShell->setHoldingPosition(this);
            holdShell->draw(deltaTime);
        }
    }

    if (currentAnimation == nullptr) return;
    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    updateTime(deltaTime);
    
    
    if (isHolding()) {
        if (isJumping()) {
            if (getState() == STARMAN) {
                currentAnimation->update(deltaTime, 0, 3);
            }
            else currentAnimation->update(deltaTime, 1, 1);
            currentAnimation->render(getPosition());
        }
        else if (isIdle()) {
            if (getState() == STARMAN) {
                currentAnimation->update(deltaTime, 0, 3);
            }
            else currentAnimation->update(deltaTime, 0, 1);
            currentAnimation->render(getPosition());
        }
        else {
            currentAnimation->update(deltaTime);
            currentAnimation->render(getPosition());
        }
        return;
    }

    currentAnimation->update(deltaTime);
    currentAnimation->render(getPosition());
}

void Character::setPhase(Phase phase) {
	this->phase = phase;
}

const Character::Phase& Character::getPhase() const {
	return phase;
}

void Character::onKey(KeyboardKey key, bool pressed) {
    if (isDead()) return;

    if (key == KEY_R && pressed) {
        if ((state->getState() == FIRE || state->getState() == FIRESTARMAN) && countThrowTime >= TIME_BETWEEN_THROWS) {
            Fireball* fireball = new Fireball();
            fireball->setCharacterPositionBall(this);
            if (orientation == RIGHT) {
                setAnimation(throwRight, throwRight->getAnimationTime());
            }
            else if (orientation == LEFT) {
                setAnimation(throwLeft, throwLeft->getAnimationTime());
            }
            setXVelocity(0.f);
            if (fireball != nullptr) {
                globalGameEngine->addFireBall(fireball);
            }

            countThrowTime = 0.f;
        }
    }
}

void Character::update(float deltaTime) {
    if (isDead()) return;
    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
        if (!isInvicible()) {
            invicibleTime = 0.f;
            transform(lastState);
        }
    }

    if (phase == DEFAULT_PHASE) {
        //Hold shell
        if (IsKeyUp(KEY_LEFT_SHIFT)) {
            setHolding(false);
            if (holdShell != nullptr) {
                holdShell->setOrientation(getOrientation());
                if (orientation == RIGHT) {
                    holdShell->setXPosition(getRight());
                    holdShell->setXVelocity(getVelocity().x + 1000.f);
                    holdShell->kicked(RIGHT);
                }
                else if (orientation == LEFT) {
                    holdShell->setXPosition(getLeft() - holdShell->getSize().x);
                    holdShell->setXVelocity(getVelocity().x - 1000.f);
                    holdShell->kicked(LEFT);
                }
                holdShell->setGravityAvailable(true);
                holdShell->setIsHold(false);
                holdShell = nullptr;
                RESOURCE_MANAGER.playSound("kick.wav");
            }
        }
        else if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (holdShell != nullptr && holdShell->isDead()) {
                holdShell = nullptr;
                setHolding(false);
            }
        }

        state->update(deltaTime);
        INPUT_MANAGER.update();
        countThrowTime += deltaTime;
    }
    else if (phase == TRANSFORM_PHASE) {
        //transform
    }
    else if (phase == DEAD_PHASE) {
        //dead
    }
    else if (phase == EXIT_PHASE) {
        //exit
    }
    else if (phase == ENTER_PHASE) {
        //enter
    }

    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
        if (isInvicible()) {
            invicibleTime -= deltaTime;
        }
    }
}

bool Character::isInvicible() const { return invicibleTime > 0.f; }

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

void Character::setHoldAnimation() {
    if (orientation == RIGHT) setAnimation(holdRight);
    else if (orientation == LEFT) setAnimation(holdLeft);
}

void Character::setInvicible(float invicibleTime) {
    this->invicibleTime = invicibleTime;
}

void Character::setSitting(bool sitting) {
    this->sitting = sitting;
}

void Character::transform(STATE type) {
    Character* character = state->getCharacter();
    free(state);
    if (type == NORMAL) {
        state = new NormalState(character);
        lastState = NORMAL;
    }
    else if (type == SUPER) {
        state = new SuperState(character);
        lastState = SUPER;
    }
    else if (type == FIRE) {
        state = new FireState(character);
        lastState = FIRE;
    }
    else if (type == STARMAN) {
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
    Effect* text = nullptr;
    Vector2 vector2 = {getCenterX(), getTop()};
    if (item->getItemType() == MUSHROOM) {
		const Mushroom* mushroom = dynamic_cast<const Mushroom*>(item);
        if (mushroom->getMushroomType() == MUSHROOM_SUPER) {
            scores += mushroom->POINT;
			if (getState() == NORMAL) {
				transform(SUPER);
				//phase = TRANSFORM_PHASE;
			}
			RESOURCE_MANAGER.playSound("power_up.wav");
            text = new TextEffect(to_string(mushroom->POINT).c_str(), vector2);
        }
        else if (mushroom->getMushroomType() == MUSHROOM_1UP) {
            lives++;
            RESOURCE_MANAGER.playSound("1_up.wav");
            text = new TextEffect("1 UP", vector2);
        }
    }
    else if (item->getItemType() == FLOWER) {
		const Flower* flower = dynamic_cast<const Flower*>(item);
        if (flower->getFlowerType() == FIRE_FLOWER) {
            scores += flower->POINT;
            if (getState() == NORMAL) {
                transform(FIRE);
				//phase = TRANSFORM_PHASE;
            }
            RESOURCE_MANAGER.playSound("power_up.wav");
            text = new TextEffect(to_string(flower->POINT).c_str(), vector2);
        }
    }
	else if (item->getItemType() == STAR) {
		const Star* star = dynamic_cast<const Star*>(item);
        if (star->getStarType() == YELLOW_STAR) {
            if (getState() == NORMAL) {
                transform(STARMAN);
                //phase = TRANSFORM_PHASE;
            }
            else if (getState() == SUPER) {
                transform(SUPERSTARMAN);
                //phase = TRANSFORM_PHASE;
            }
            else if (getState() == FIRE) {
                transform(FIRESTARMAN);
                //phase = TRANSFORM_PHASE;
            }
    
            invicibleTime = INVICIBLE_TIME;
			scores += star->POINT;
			RESOURCE_MANAGER.playSound("power_up.wav");
    
            text = new TextEffect(to_string(star->POINT).c_str(), vector2);
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

    if (text != nullptr) {
        globalGameEngine->addEffect(text);
    }
};


//True if character stomp, kick or starman. Otherwise it false
void Character::collisionWithEnemy(Enemy* enemy, Edge edge) {
    if (enemy == nullptr) return;

    Shell* shell = dynamic_cast<Shell*>(enemy);
    if (shell && shell == getHoldShell()) return;

    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
        scores += 100;
        RESOURCE_MANAGER.playSound("stomp.wav");
        enemy->attacked();
    }
    else if (enemy->getEnemyType() != SHELL) {
        if (edge == TOP_EDGE && enemy->getEnemyType() != PLANT) {
            scores += 100;
            setYVelocity(JET_STOMP_VELOCITY);
            setJumping(true);
            RESOURCE_MANAGER.playSound("stomp.wav");
            enemy->stomped();
        }
        else {
            if (state->getState() == NORMAL) {
                lives--;
                setLostLife(true);
                RESOURCE_MANAGER.playSound("lost_life.wav");
            }
            else if (state->getState() == SUPER) {
                transform(NORMAL);
                RESOURCE_MANAGER.playSound("lost_suit.wav");
            }
            else if (state->getState() == FIRE) {
                transform(NORMAL);
                RESOURCE_MANAGER.playSound("lost_suit.wav");
            }
        }
    }   
    else if (enemy->getEnemyType() == SHELL) {
        Shell* shell = dynamic_cast<Shell*>(enemy);
        if (edge == TOP_EDGE || edge == BOTTOM_EDGE) {
            setYVelocity(JET_STOMP_VELOCITY);
            setJumping(true);
            RESOURCE_MANAGER.playSound("stomp.wav");
            shell->stomped(getCenter());
        }
        else {
            if (enemy->isIdle()) {
                if (edge == LEFT_EDGE) {
                    if (IsKeyDown(KEY_LEFT_SHIFT)) {
                        setHolding(true);
                        setHoldingShell(shell);
                        shell->setGravityAvailable(false);
                    }
                    else {
                        shell->kicked(RIGHT);
                        setAnimation(kickRight, 0.2f);
                        RESOURCE_MANAGER.playSound("kick.wav");
                    }
                }
                else if (edge == RIGHT_EDGE) {
                    if (IsKeyDown(KEY_LEFT_SHIFT)) {
                        setHolding(true);
                        setHoldingShell(shell);
                        shell->setGravityAvailable(false);
                        setAnimation(holdLeft);
                    }
                    else {
                        shell->kicked(LEFT);
                        setAnimation(kickLeft, 0.2f);
                        RESOURCE_MANAGER.playSound("kick.wav");
                    }
                }
            }
            else {
                if (state->getState() == NORMAL) {
                    lives--;
                    setLostLife(true);
                    RESOURCE_MANAGER.playSound("lost_life.wav");
                }
                else if (state->getState() == SUPER) {
                    transform(NORMAL);
                    RESOURCE_MANAGER.playSound("lost_suit.wav");
                }
                else if (state->getState() == FIRE) {
                    transform(NORMAL);
                    RESOURCE_MANAGER.playSound("lost_suit.wav");
                }
            }
        }
    }
    
}