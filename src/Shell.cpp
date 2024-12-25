#include"../include/Shell.h"
#include"../include/GameEngine.h"
#include"../include/KoopaTroopa.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

Shell::~Shell() {
	free(inShell);
	free(outShell);
	free(shellSpin);
	inShell = nullptr;
	outShell = nullptr;
	shellSpin = nullptr;
}

Shell::Shell(ShellType type, Vector2 position) : Enemy(position) {
	this->type = type;
	this->inShellTime = 0.f;
	this->isKicked = false;
	this->isHold = false;
	inShell = nullptr;
	outShell = nullptr;
	shellSpin = nullptr;

	if (type == GREEN_SHELL) {
		inShell = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_shell")->clone();
		outShell = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_outShell")->clone();
		shellSpin = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_spin")->clone();
	}
	else if (type == RED_SHELL) {
		inShell = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_shell")->clone();
		outShell = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_outShell")->clone();
		shellSpin = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_spin")->clone();
	}

	setAnimation(inShell);
}

EnemyType Shell::getEnemyType() const  {
	return EnemyType::SHELL;
}

void Shell::update(float deltaTime)  {
	Sprite::update(deltaTime);

	if (isDead()) return;
	if (inShellTime >= IN_SHELL_TIME) {
		killEntity();
		KoopaTroopa* enemy = nullptr;
		if (type == GREEN_SHELL) {
			enemy = new KoopaTroopa(GREEN_KoopaTroopa, getPosition(), getRandomOrientation());
		}
		else if (type == RED_SHELL) {
			enemy = new KoopaTroopa(RED_KoopaTroopa, getPosition(), getRandomOrientation());
		}
		float diffHeight = 0.f;
		if (enemy) diffHeight = getSize().y - enemy->getSize().y;
		enemy->setYPosition(getY() + diffHeight);
		globalGameEngine->addEnemy(enemy);
		return;
	}

	if (isKicked) inShellTime = 0.f;
	else inShellTime += deltaTime;

	if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
	else if (getPosition().x >= getBoundary().y) setOrientation(LEFT);

	if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);
	if (isKicked) {
		if (orientation) setXVelocity(SPIN_SPEED);
		else setXVelocity(-SPIN_SPEED);
		setAnimation(shellSpin);
	}
	else if (isHold) {
		//Do nothing
	}
	else {
		setXVelocity(0.f);
		if (inShellTime < IN_SHELL_TIME - OUT_SHELL_TIME) {
			setAnimation(inShell);
		}
	}

	if (inShellTime >= IN_SHELL_TIME - OUT_SHELL_TIME) {
		setAnimation(outShell);
	}
}

void Shell::setIsHold(bool hold) {
	this->isHold = hold;
}

bool Shell::getIsHold() const {
	return this->isHold;
}

void Shell::setIsKicked(bool kicked) {
	this->isKicked = kicked;
}

bool Shell::getIsKicked() const {
	return this->isKicked;
}

void Shell::kicked(Orientation direction) {
	setOrientation(direction);
	isKicked = true;
}

void Shell::stomped(Vector2 center) {
	if (isKicked == true) {
		isKicked = false;
		return;
	}

	if (getCenter().x > center.x) {
		setOrientation(RIGHT);
	}
	else if (getCenter().x < center.x) {
		setOrientation(LEFT);
	}
	else setOrientation(getRandomOrientation());
	isKicked = true;
}

void Shell::attacked(Orientation direction) {
	Enemy::attacked();

	Effect* dead = nullptr;
	if (type == GREEN_SHELL) {
		dead = new Effect(RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_up_spin")->clone(), getPosition(), 999.f);
	}
	else if (type == RED_SHELL) {
		dead = new Effect(RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_up_spin")->clone(), getPosition(), 999.f);
	}

	if (dead) dead->setVelocity({ direction == RIGHT ? DEAD_INITIAL_VELOCITY_X : -DEAD_INITIAL_VELOCITY_X , -DEAD_INITIAL_VELOCITY_Y });

	globalGameEngine->addEffect(dead);
}

void Shell::setHoldingPosition(const Character* character) {
	if (character == nullptr) return;

	setCenter(character->getCenter());

	if (character->getOrientation()) {
		setXPosition(character->getRight() - getSize().y / 4.f);
	}
	else {
		setXPosition(character->getLeft() - 3.f * getSize().y / 4.f);
	}

	setVelocity(character->getVelocity());
}