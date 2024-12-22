#include "../include/GoomBa.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

GoomBa::~GoomBa() {
	free(walkAnimation);
	free(jumpAnimation);
	walkAnimation = nullptr;
	jumpAnimation = nullptr;
	deadAnimation = nullptr;
}

GoomBa::GoomBa(GoomBaType type, Vector2 position, Orientation orientation) : Enemy(position) {
	this->type = type;
	this->jumpTime = 0.f;
	this->canJump = false;
	this->orientation = orientation;
	setXVelocity(orientation == RIGHT ? SPEED : -SPEED);
	setYVelocity(0.f);

	walkAnimation = nullptr;
	jumpAnimation = nullptr;
	deadAnimation = nullptr;

	if (type == BROWN_GoomBa) {
		walkAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba")->clone();
		deadAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba_dead");
	}
	else if (type == RED_GoomBa) {
		walkAnimation = RESOURCE_MANAGER.getAnimation("red_goomba")->clone();
		deadAnimation = RESOURCE_MANAGER.getAnimation("red_goomba_dead");
	}
	else if (type == BROWNPARA_GoomBa) {
		walkAnimation = RESOURCE_MANAGER.getAnimation("brown_paragoomba")->clone();
		jumpAnimation = RESOURCE_MANAGER.getAnimation("brown_paragoomba_jump")->clone();
		deadAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba_dead");
		this->canJump = true;
	}
	else if (type == REDPARA_GoomBa) {
		walkAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba")->clone();
		jumpAnimation = RESOURCE_MANAGER.getAnimation("red_paragoomba_jump")->clone();
		deadAnimation = RESOURCE_MANAGER.getAnimation("red_goomba_dead");
		this->canJump = true;
	}

	setAnimation(walkAnimation);
}

EnemyType GoomBa::getEnemyType() const {
	return EnemyType::GOOMBA;
}

void GoomBa::update(float deltaTime) {
	if (isDead()) return;

	if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
	else if (getPosition().x >= getBoundary().y) setOrientation(LEFT);

	if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

	if (jumpTime >= TIME_PER_JUMP && canJump) {
		setYVelocity(-JUMP_SPEED);
		setAnimation(jumpAnimation);
		setJumping(true);
		jumpTime = 0.f;
	}

	if (orientation) setXVelocity(SPEED);
	else setXVelocity(-SPEED);


	if (isJumping() == false) {
		setAnimation(walkAnimation);
		jumpTime += deltaTime;
	}
}

void GoomBa::stomped() {
	if (isDead()) return;

	if (type == BROWN_GoomBa || type == RED_GoomBa) {
		killEntity();
		setCollisionAvailable(false);
		setAnimation(deadAnimation);
		Effect* deadEffect = new Effect(deadAnimation->clone(), getPosition(), DEAD_TIME);
		deadEffect->setGravityAvailable(false);
		globalGameEngine->addEffect(deadEffect);
	}
	else if (type == REDPARA_GoomBa) {
		type = RED_GoomBa;
		free(jumpAnimation);
		free(walkAnimation);
		jumpAnimation = nullptr;
		walkAnimation = RESOURCE_MANAGER.getAnimation("red_goomba")->clone();
		canJump = false;
		currentAnimation = nullptr;
		setJumping(false);
		jumpTime = 0.f;
	}
	else if (type == BROWNPARA_GoomBa) {
		type = BROWN_GoomBa;
		free(jumpAnimation);
		free(walkAnimation);
		jumpAnimation = nullptr;
		currentAnimation = nullptr;
		walkAnimation = RESOURCE_MANAGER.getAnimation("brown_goomba")->clone();
		canJump = false;
		setJumping(false);
		jumpTime = 0.f;
	}

	Effect* text = new TextEffect(to_string(ENEMY_POINT).c_str(), getCenter());
	globalGameEngine->addEffect(text);
}