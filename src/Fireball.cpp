#include"../include/Fireball.h"
#include"../include/BaseBlock.h"
#include"../include/Character.h"
#include"../include/GameEngine.h"
#include"../include/Effect.h"
#include"../include/TextEffect.h"

Fireball::~Fireball() {
	free(fireRight);
	free(fireLeft);
	fireLeft = nullptr;
	fireRight = nullptr;
}

Fireball::Fireball(Vector2 center , FireballType type, Orientation orientation) {
	this->type = type;
	this->orientation = orientation;
	this->delayTime = 0.f;
	this->delayVelocity = { 0.f, 0.f };
	this->soundEffect = false;

	fireLeft = RESOURCE_MANAGER.getAnimation("fireball_left")->clone();
	fireRight = RESOURCE_MANAGER.getAnimation("fireball_right")->clone();

	//fireLeft->setScale(5.f);
	//fireRight->setScale(5.f);

	if (orientation == LEFT) setAnimation(fireLeft);
	else if (orientation == RIGHT) setAnimation(fireRight);

	setCenter(center);
}

const FireballType& Fireball::getFireballType() const {
	return this->type;
}

EntityType Fireball::getType() const {
	return EntityType::FIREBALL;
}

void Fireball::setDelayTime(float delayTime) {
	this->delayTime = -delayTime;
}

float Fireball::getDelayTime() const {
	return delayTime;
}

void Fireball::calculateFireballVelocity(const Vector2& fireballPos, const Vector2& playerPos, float speed) {
	if (speed == 0.f) {
		if (type == ENEMY_FIREBALL) speed = ENEMY_FIREBALL_SPEED;
		else if (type == CHARACTER_FIREBALL) speed = CHARACTER_FIREBALL_SPEED;
	}

	Vector2 direction = { playerPos.x - fireballPos.x, playerPos.y - fireballPos.y };

	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	Vector2 velocity = { (direction.x / magnitude) * speed, (direction.y / magnitude) * speed };

	if (velocity.x < 0) setAnimation(fireLeft);
	else if (velocity.x > 0) setAnimation(fireRight);

	delayVelocity = velocity;
}

void Fireball::setCharacterPositionBall(const Character* character) {
	if (character == nullptr) return;

	if (character->getOrientation() == LEFT) {
		setAnimation(fireLeft);
		setOrientation(LEFT);
		setPosition({ character->getLeft() + getSize().x / 2.f, character->getTop() + character->getSize().y / 4.f });
		setXVelocity(-CHARACTER_FIREBALL_SPEED);
	}
	else if (character->getOrientation() == RIGHT) {
		setAnimation(fireRight);
		setOrientation(RIGHT);
		setPosition({ character->getRight() - getSize().x / 2.f, character->getTop() + character->getSize().y / 4.f });
		setXVelocity(CHARACTER_FIREBALL_SPEED);
	}
}

void Fireball::update(float deltaTime) {
	if (orientation == LEFT) setAnimation(fireLeft);
	else if (orientation == RIGHT) setAnimation(fireRight);

	if (type == CHARACTER_FIREBALL) {
		if (delayTime >= 0.f) {
			if (orientation == RIGHT) setXVelocity(CHARACTER_FIREBALL_SPEED);
			else if (orientation == LEFT) setXVelocity(-CHARACTER_FIREBALL_SPEED);
			if (isGravityAvailable() == true) setYVelocity(getVelocity().y + GRAVITY * deltaTime);
		}

		if (delayTime < 0.f) delayTime += deltaTime;
	}
	else if (type == ENEMY_FIREBALL) {
		if (delayTime >= ENEMY_FIREBALL_LIFETIME) {
			killEntity();
			return;
		}
		if (delayTime >= 0.f) {
			setVelocity(delayVelocity);
			//if (soundEffect == false) RESOURCE_MANAGER.playSound("shot.wav");
			soundEffect = true;
		}

		delayTime += deltaTime;
		delayTime = min(delayTime, ENEMY_FIREBALL_LIFETIME);
	}
}

void Fireball::collisionWithBlock(const BaseBlock* block, Edge edge) {
	if (block == nullptr) return;

	if (type == ENEMY_FIREBALL) return;

	if (edge == TOP_EDGE) {
		setYVelocity(BOUNCE_VELOCITY);
	}
	else if (edge == BOTTOM_EDGE) {
		setYVelocity(-BOUNCE_VELOCITY);
	}
	else {
		killEntity();
		setCollisionAvailable(false);
		Effect* smoke = new Effect(RESOURCE_MANAGER.getAnimation("smoke")->clone(), getPosition(), true, 0.f);
		smoke->setGravityAvailable(false);
		globalGameEngine->addEffect(smoke);
		RESOURCE_MANAGER.playSound("bump.wav");
	}
}