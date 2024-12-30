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
#include"../include/BaseBlock.h"

Character::Character(Vector2 pos, Vector2 size) : Sprite(pos, size)
, inputManager(INPUT_MANAGER) {
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    holding = false;
    lostLife = false;
    invicibleStarTime = 0.f;
    sitting = false;
    state = nullptr;
    holdShell = nullptr;
    movingBlockStandOn = nullptr;
    countThrowTime = 0.f;
    countImmortalTime = 0.f;
    specificVelocity = { 0.f, 0.f };
    renderImmortal = { true, true, true, true, true, true, false, false, false, false, false, false };
    indexRender = 0u;
    standingUp = false;

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

    deadAniamtion = nullptr;
};

Character::~Character() {
    free(state);
    state = nullptr;
    INPUT_MANAGER.removeListener(*this);
}

EntityType Character::getType() const { return EntityType::CHARACTER; }

void Character::reset() {
    setPosition({ 16, 400 });
    setVelocity({ 0,0 });
    scores = 0;
    coins = 0;
    lives = 5;
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    holding = false;
    lostLife = false;
    invicibleStarTime = 0.f;
    sitting = false;
    holdShell = nullptr;
    movingBlockStandOn = nullptr;
    countThrowTime = 0.f;
    countImmortalTime = 0.f;
    specificVelocity = { 0.f, 0.f };
    transform(NORMAL);
    setCollisionAvailable(true);
}
void Character::resetInGame()
{
    setPosition({ 16, 400 });
    setVelocity({ 0,0 });
    phase = DEFAULT_PHASE;
    orientation = RIGHT;
    jumping = false;
    holding = false;
    lostLife = false;
    invicibleStarTime = 0.f;
    sitting = false;
    holdShell = nullptr;
    movingBlockStandOn = nullptr;
    countThrowTime = 0.f;
    countImmortalTime = 0.f;
    specificVelocity = { 0.f, 0.f };
    transform(NORMAL);
    setCollisionAvailable(true);
}

STATE Character::getState() const {
    return state->getState();
}

void Character::draw(float deltaTime) {
    if (isHolding() && holdShell) {
        if (holdShell->isDead() == false) {
            holdShell->setHoldingPosition(this);
            holdShell->draw(deltaTime);
        }
    }

    if (currentAnimation == nullptr) return;
    specificVelocity = getVelocity();

    if (movingBlockStandOn != nullptr) {
        setXVelocity(specificVelocity.x + movingBlockStandOn->getVelocity().x);
        setYVelocity(specificVelocity.y + movingBlockStandOn->getVelocity().y);
    }

    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    updateTime(deltaTime);

    setVelocity(specificVelocity);
    
    
    if (isHolding()) {
        if (isJumping()) {
            if (getState() == STARMAN) {
                currentAnimation->update(deltaTime, 0, 3);
            }
            else if (getState() == SUPERSTARMAN) {
                currentAnimation->update(deltaTime, 12, 3);
            }
            else if (getState() == FIRESTARMAN) {
                currentAnimation->update(deltaTime, 12, 3);
            }
            else currentAnimation->update(deltaTime, 1, 1);
        }
        else if (isIdle()) {
            if (getState() == STARMAN) {
                currentAnimation->update(deltaTime, 0, 3);
            }
            else if (getState() == SUPERSTARMAN) {
                currentAnimation->update(deltaTime, 9, 3);
            }
            else if (getState() == FIRESTARMAN) {
                currentAnimation->update(deltaTime, 9, 3);
            }
            else currentAnimation->update(deltaTime, 0, 1);
        }
        else {
            currentAnimation->update(deltaTime);
        }
    }
    else currentAnimation->update(deltaTime);
    

    if (countImmortalTime > 0.f) {
        if (renderImmortal[indexRender]) {
            currentAnimation->render(getPosition());
        }
    }
    else currentAnimation->render(getPosition());
}

void Character::setPhase(Phase phase) {
    if (phase == DEAD_PHASE) {
        setXVelocity(0.f);
        setYVelocity(-DEAD_PLAYER_INITIAL_VELOCITY);
        setCollisionAvailable(false);
        setMovingBlockStandOn(nullptr);
        setHoldingShell(nullptr);
        setHolding(false);
        setAnimation(deadAniamtion);
        lives--;
    }
    else if (phase == CLEARLEVEL_PHASE) {
        setYVelocity(0.f);
        setXVelocity(MAX_WALK_VELOCITY);
    }
	this->phase = phase;
}

const Character::Phase& Character::getPhase() const {
	return phase;
}

void Character::onKey(KeyboardKey key, bool pressed) {
    if (isDead()) return;

    if (key == KEY_W && pressed) {
        if ((state->getState() == FIRE || state->getState() == FIRESTARMAN || state->getState() == SUPERSTARMAN) && countThrowTime > 0.f && holdShell == nullptr) {
            Fireball* fireball = new Fireball();
            fireball->setCharacterPositionBall(this);
            if (orientation == RIGHT) {
                setAnimation(throwRight, throwRight->getAnimationTime());
                fireball->setXVelocity(0.f);
            }
            else if (orientation == LEFT) {
                fireball->setXVelocity(0.f);
                setAnimation(throwLeft, throwLeft->getAnimationTime());
            }
            setXVelocity(getVelocity().x / 2.f);
            if (fireball != nullptr) {
                globalGameEngine->addFireBall(fireball);
            }

            countThrowTime -= FIREBALL_CHARGE_TIME;
        }
    }
}

void Character::update(float deltaTime) {
    //if (isDead()) return;
    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
        if (!isInvicible()) {
            invicibleStarTime = 0.f;
            lostSuit();
        }
    }

    if (phase == DEFAULT_PHASE) {
        if (IsKeyReleased(KEY_S) && isSitting()) standingUp = true;
        else standingUp = false;

        state->update(deltaTime); 
        INPUT_MANAGER.update();
        countThrowTime += deltaTime; 
        countThrowTime = min(countThrowTime, 3.f);

        if (countImmortalTime > 0.f) {
            countImmortalTime = max(0.f, countImmortalTime - deltaTime);
            indexRender = (indexRender + 1) % renderImmortal.size();
            RESOURCE_MANAGER.playSound("../../assets/Sound/lost_suit.wav");
        }

        //Hold shell
        if (IsKeyUp(KEY_LEFT_SHIFT)) {
            setHolding(false);
            if (holdShell != nullptr) {
                holdShell->setOrientation(getOrientation());
                if (orientation == RIGHT) {
                    holdShell->setXPosition(getRight());
                    holdShell->setXVelocity(getVelocity().x + 500.f);
                    holdShell->kicked(RIGHT);
                }
                else if (orientation == LEFT) {
                    holdShell->setXPosition(getLeft() - holdShell->getSize().x);
                    holdShell->setXVelocity(getVelocity().x - 500.f);
                    holdShell->kicked(LEFT);
                }
                holdShell->setGravityAvailable(true);
                holdShell->setIsHold(false);
                holdShell = nullptr;
                RESOURCE_MANAGER.playSound("../../assets/Sound/kick.wav");
            }
        }
        else if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (holdShell != nullptr && holdShell->isDead()) {
                holdShell = nullptr;
                setHolding(false);
            }
        }

        if (movingBlockStandOn != nullptr) {
            setYVelocity(getVelocity().y + movingBlockStandOn->getVelocity().y);
        }

    }
    else if (phase == TRANSFORM_PHASE) {
        //transform
    }
    else if (phase == DEAD_PHASE) {
        //setYVelocity(getVelocity().y + DEAD_PLAYER_GRAVITY * deltaTime);
    }
    else if (phase == EXIT_PHASE) {
        //exit
    }
    else if (phase == ENTER_PHASE) {
        //enter
    }
    else if (phase == CLEARLEVEL_PHASE) {
        setYVelocity(getVelocity().y + GRAVITY * deltaTime);

        if (isJumping() == false) setAnimation(walkRight);
        else if (getState() == NORMAL || getState() == STARMAN) setAnimation(jumpRight);
        else setAnimation(fallRight);
    }

    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
        if (isInvicible()) {
            invicibleStarTime -= deltaTime;
        }
    }
}

bool Character::isInvicible() const { return invicibleStarTime > 0.f; }

bool Character::isIdle() const {
    return (velocity.x == 0.f && velocity.y == 0.f && !isJumping());
}

bool Character::isStadingUp() const { return this->standingUp; }

int Character::getLives() const { return lives; }

void Character::setLives(int lives) {
    this->lives = lives;
}
int Character::getCoins() const { return coins; }

void Character::setCoins(int coins) {
    this->coins = coins;
}

int Character::getScores() const { return scores; }

bool Character::isSitting() const {
    return sitting;
}

bool Character::isLostLife() const {
    return this->lostLife;
}
void Character::setLostLife(bool lostLife) {
    this->lostLife = lostLife;
}

void Character::setScores(int score) {
    this->scores = score;
}

void Character::setHolding(bool holding) {
    this->holding = holding;
}

bool Character::isHolding() const {
    return this->holding;
}

void Character::setHoldingShell(Shell* shell) {
    this->holdShell = shell;
}

Shell* Character::getHoldShell() const {
    return this->holdShell;
}

void Character::setMovingBlockStandOn(MovingBlock* block) {
    this->movingBlockStandOn = block;
}

MovingBlock* Character::getMovingBlockStandOn() const {
    return this->movingBlockStandOn;
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

void Character::setStarInvicibleTime(float invicibleStarTime) {
    this->invicibleStarTime = invicibleStarTime;
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

void Character::lostSuit() {
    if (state->getState() == NORMAL) {
        setLostLife(true);
        return;
    }
    else if (state->getState() == SUPER) {
        transform(NORMAL);
    }
    else if (state->getState() == FIRE) {
        transform(NORMAL);
    }
    else if (state->getState() == STARMAN) {
        transform(NORMAL);
    }
    else if (state->getState() == SUPERSTARMAN) {
        transform(SUPER);
    }
    else if (state->getState() == FIRESTARMAN) {
        transform(FIRE);
    }

    countImmortalTime = IMMORTAL_TIME;
}

void Character::collisionWithItem(const Item* item) {
    TextEffect* text = nullptr;
    Vector2 vector2 = {getCenterX(), getTop()};

    if (item->getItemType() == MUSHROOM) {
		const Mushroom* mushroom = dynamic_cast<const Mushroom*>(item);
        if (mushroom->getMushroomType() == MUSHROOM_SUPER) {
            scores += mushroom->getPoint();
			if (getState() == NORMAL) {
				transform(SUPER);
			}
            else if (getState() == STARMAN) {
                transform(SUPERSTARMAN);
            }
			RESOURCE_MANAGER.playSound("../../assets/Sound/power_up.wav");
            text = new TextEffect(to_string(mushroom->getPoint()).c_str(), vector2);
        }
        else if (mushroom->getMushroomType() == MUSHROOM_1UP) {
            lives++;
            RESOURCE_MANAGER.playSound("../../assets/Sound/1_up.wav");
            text = new TextEffect("1 UP", vector2);
            text->setTextColor(WHITE);
            text->setOutlineColor(YELLOW);
        }
    }
    else if (item->getItemType() == FLOWER) {
		const Flower* flower = dynamic_cast<const Flower*>(item);
        if (flower->getFlowerType() == FIRE_FLOWER) {
            scores += flower->getPoint();
            if (getState() == NORMAL) {
                transform(FIRE);
            }
            else if (getState() == STARMAN) {
                transform(FIRESTARMAN);
            }
            RESOURCE_MANAGER.playSound("../../assets/Sound/power_up.wav");
            text = new TextEffect(to_string(flower->getPoint()).c_str(), vector2);
        }
    }
	else if (item->getItemType() == STAR) {
		const Star* star = dynamic_cast<const Star*>(item);
        if (star->getStarType() == YELLOW_STAR) {
            if (getState() == NORMAL) {
                transform(STARMAN);
            }
            else if (getState() == SUPER) {
                transform(SUPERSTARMAN);
            }
            else if (getState() == FIRE) {
                transform(FIRESTARMAN);
            }
    
            invicibleStarTime = STAR_INVICIBLE_TIME;
			scores += star->getPoint();
			RESOURCE_MANAGER.playSound("../../assets/Sound/power_up.wav");
    
            text = new TextEffect(to_string(star->getPoint()).c_str(), vector2);
        }
	}
	else if (item->getItemType() == COIN) {
		const Coin* coin = dynamic_cast<const Coin*>(item);
		if (coin->getCoinType() == STATIC_COIN) {
			coins++;
			scores += coin->getPoint();
			RESOURCE_MANAGER.playSound("../../assets/Sound/coin.wav");
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
        RESOURCE_MANAGER.playSound("../../assets/Sound/stomp.wav");
        enemy->attacked(getOrientation());
    }
    else if (enemy->getEnemyType() != SHELL) {
        if (edge == TOP_EDGE && enemy->getEnemyType() != PLANT) {
            scores += 100;
            setYVelocity(JET_STOMP_VELOCITY);
            setJumping(true);
            RESOURCE_MANAGER.playSound("../../assets/Sound/stomp.wav");
            enemy->stomped();
        }
        else if (countImmortalTime > 0.f) return;
        else lostSuit();
    }   
    else if (enemy->getEnemyType() == SHELL) {
        Shell* shell = dynamic_cast<Shell*>(enemy);
        if (edge == TOP_EDGE || edge == BOTTOM_EDGE) {
            setYVelocity(JET_STOMP_VELOCITY);
            setJumping(true);
            RESOURCE_MANAGER.playSound("../../assets/Sound/stomp.wav");
            shell->stomped(getCenter());
        }
        else {
            if (!shell->getIsHold() && !shell->getIsKicked()) {
                if (edge == LEFT_EDGE) {
                    if (IsKeyDown(KEY_LEFT_SHIFT)) {
                        setHolding(true);
                        setHoldingShell(shell);
                        shell->setGravityAvailable(false);
                        shell->setIsHold(true);
                    }
                    else {
                        shell->kicked(RIGHT);
                        setAnimation(kickRight, 0.2f);
                        RESOURCE_MANAGER.playSound("../../assets/Sound/kick.wav");
                    }
                }
                else if (edge == RIGHT_EDGE) {
                    if (IsKeyDown(KEY_LEFT_SHIFT)) {
                        setHolding(true);
                        setHoldingShell(shell);
                        shell->setGravityAvailable(false);
                        shell->setIsHold(true);
                    }
                    else {
                        shell->kicked(LEFT);
                        setAnimation(kickLeft, 0.2f);
                        RESOURCE_MANAGER.playSound("../../assets/Sound/kick.wav");
                    }
                }
            }
            else if (countImmortalTime > 0.f) return;
            else lostSuit();
        }
    }
}

void Character::collisionWithFireball(Fireball* fireball) {
    if (countImmortalTime > 0.f) return;

    if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) return;
    lostSuit();
    fireball->killEntity();
}