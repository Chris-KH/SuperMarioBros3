#include "../include/KoopaTroopa.h"
#include "../include/Shell.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

KoopaTroopa::KoopaTroopa(KoopaTroopaType type, Vector2 position , Orientation orientation) : Enemy(position) {
	this->type = type;
	this->jumpTime = 0.f;
	this->canJump = false;
	this->orientation = orientation;
	setXVelocity(orientation == RIGHT ? SPEED : -SPEED);
	setYVelocity(0.f);

	walkLeft = nullptr;
	walkRight = nullptr;
	jumpLeft = nullptr;
	jumpRight = nullptr;

	if (type == GREEN_KoopaTroopa) {
		walkLeft = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkRight")->clone();
	}
	else if (type == RED_KoopaTroopa) {
		walkLeft = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkRight")->clone();
	}
	else if (type == GREENPARA_KoopaTroopa) {
		walkLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_walkRight")->clone();
		jumpLeft = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpLeft")->clone();
		jumpRight = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_jumpRight")->clone();
		this->canJump = true;
	}
	else if (type == REDPARA_KoopaTroopa) {
		walkLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_walkRight")->clone();
		jumpLeft = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpLeft")->clone();
		jumpRight = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_jumpRight")->clone();
		this->canJump = true;
	}

	if (orientation) setAnimation(walkRight);
	else setAnimation(walkLeft);
}

KoopaTroopa::~KoopaTroopa() {
	free(walkLeft);
	free(walkRight);
	free(jumpLeft);
	free(jumpRight);
	walkLeft = nullptr;
	walkRight = nullptr;
	jumpLeft = nullptr;
	jumpRight = nullptr;
}

EnemyType KoopaTroopa::getEnemyType() const {
	return EnemyType::KOOPATROOPA;
}

void KoopaTroopa::update(float deltaTime) {
	Sprite::update(deltaTime);

	if (isDead()) return;

	if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
	else if (getRight() >= getBoundary().y) setOrientation(LEFT);

	if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

	if (jumpTime >= TIME_PER_JUMP && canJump) {
		setYVelocity(-JUMP_SPEED);
		if (orientation) setAnimation(jumpRight);
		else setAnimation(jumpLeft);
		setJumping(true);
		jumpTime = 0.f;
	}

	if (orientation) setXVelocity(SPEED);
	else setXVelocity(-SPEED);

	if (isJumping() == false) {
		if (orientation) setAnimation(walkRight);
		else setAnimation(walkLeft);
		jumpTime += deltaTime;
	}
}

void KoopaTroopa::stomped() {
	if (isDead()) return;

	if (type == GREEN_KoopaTroopa) {
		killEntity();
		setCollisionAvailable(false);
		Shell* shell = new Shell(GREEN_SHELL, getPosition());
		globalGameEngine->addShell(shell);
	}
	else if (type == RED_KoopaTroopa) {
		killEntity();
		setCollisionAvailable(false);
		Shell* shell = new Shell(RED_SHELL, getPosition());
		globalGameEngine->addShell(shell);
	}
	else if (type == GREENPARA_KoopaTroopa) {
		type = GREEN_KoopaTroopa;
		free(jumpLeft);
		free(jumpRight);
		free(walkLeft);
		free(walkRight);
		jumpLeft = nullptr;
		currentAnimation = nullptr;
		setJumping(false);
		jumpRight = nullptr;
		walkLeft = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_walkRight")->clone();
		canJump = false;
		jumpTime = 0.f;
	}
	else if (type == REDPARA_KoopaTroopa) {
		type = RED_KoopaTroopa;
		free(jumpLeft);
		free(jumpRight);
		free(walkLeft);
		free(walkRight);
		jumpLeft = nullptr;
		jumpRight = nullptr;
		currentAnimation = nullptr;
		setJumping(false);
		walkLeft = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkLeft")->clone();
		walkRight = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_walkRight")->clone();
		canJump = false;
		jumpTime = 0.f;
	}

	Effect* text = new TextEffect(to_string(ENEMY_POINT).c_str(), getCenter());
	globalGameEngine->addEffect(text);
}

void KoopaTroopa::attacked(Orientation direction) {
	Enemy::attacked();

	Effect* dead = nullptr;
	if (type == GREENPARA_KoopaTroopa || type == GREEN_KoopaTroopa) {
		dead = new Effect(RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_up_spin")->clone(), getPosition(), 999.f);
	}
	else if (type == REDPARA_KoopaTroopa || type == RED_KoopaTroopa) {
		dead = new Effect(RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_up_spin")->clone(), getPosition(), 999.f);
	}

	if (dead) dead->setVelocity({ direction == RIGHT ? DEAD_INITIAL_VELOCITY_X : -DEAD_INITIAL_VELOCITY_X , -DEAD_INITIAL_VELOCITY_Y });

	globalGameEngine->addEffect(dead);
}