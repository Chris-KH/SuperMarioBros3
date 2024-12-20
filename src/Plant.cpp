#include "../include/Plant.h"
#include "../include/Character.h"
#include "../include/Fireball.h"
#include "../include/GameEngine.h"

Plant::~Plant() {
	free(piranha);
	free(firePiranhaRest);
	free(firePiranhaAttack);
	piranha = nullptr;
	firePiranhaRest = nullptr;
	firePiranhaAttack = nullptr;
}

Plant::Plant(PlantType type, Vector2 position, Orientation orientation, Character* player) {
	this->type = type;
	this->player = player;
	this->timer = 0.f;

	setXVelocity(0.f);
	setYVelocity(0.f);
	setGravityAvailable(false);
	
	this->piranha = nullptr;
	this->firePiranhaRest = nullptr;
	this->firePiranhaAttack = nullptr;
	this->direction = UPLEFT;
	this->orientation = UP;
	this->phase = WAIT_PHASE;

	if (type == GREEN_PIRANHA) {
		this->piranha = RESOURCE_MANAGER.getAnimation("green_piranha")->clone();
		setAnimation(this->piranha);
	}
	else if (type == RED_PIRANHA) {
		this->piranha = RESOURCE_MANAGER.getAnimation("red_piranha")->clone();
		setAnimation(this->piranha);
	}
	else if (type == GREEN_FIREPIRANHA) {
		this->firePiranhaRest = RESOURCE_MANAGER.getAnimation("green_firepiranha")->clone();
		this->firePiranhaAttack = RESOURCE_MANAGER.getAnimation("green_firepiranha_attack")->clone();
		setAnimation(this->firePiranhaRest);
	}
	else if (type == RED_FIREPIRANHA) {
		this->firePiranhaRest = RESOURCE_MANAGER.getAnimation("red_firepiranha")->clone();
		this->firePiranhaAttack = RESOURCE_MANAGER.getAnimation("red_firepiranha_attack")->clone();
		setAnimation(this->firePiranhaRest);
	}

	setPosition(position);
}

EnemyType Plant::getEnemyType() const {
	return EnemyType::PLANT;
}

void Plant::update(float deltaTime) {
	if (isDead()) return;
	
	if (phase == EXIT_PHASE && getPosition().y <= getBoundary().x) {
		phase = ATTACK_PHASE;
		orientation = UP;
		if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) {
			setAnimation(firePiranhaAttack);
			Fireball* fireball = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball->calculateFireballVelocity(fireball->getCenter(), player->getCenter());
			fireball->setDelayTime(ATTACK_TIME / 2.f);
			globalGameEngine->addFireBall(fireball);

			//Chill
			/*Fireball* fireball1 = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball1->calculateFireballVelocity(fireball1->getCenter(), player->getCenter());
			fireball1->setDelayTime(0.f);
			globalGameEngine->addFireBall(fireball1);

			Fireball* fireball2 = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball2->calculateFireballVelocity(fireball2->getCenter(), player->getCenter());
			fireball2->setDelayTime(0.5f);
			globalGameEngine->addFireBall(fireball2);

			Fireball* fireball3 = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball3->calculateFireballVelocity(fireball3->getCenter(), player->getCenter());
			fireball3->setDelayTime(1.0f);
			globalGameEngine->addFireBall(fireball3);

			Fireball* fireball4 = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball4->calculateFireballVelocity(fireball4->getCenter(), player->getCenter());
			fireball4->setDelayTime(1.5f);
			globalGameEngine->addFireBall(fireball4);

			Fireball* fireball5 = new Fireball(getCentral(), ENEMY_FIREBALL);
			fireball5->calculateFireballVelocity(fireball5->getCenter(), player->getCenter());
			fireball5->setDelayTime(2.f);
			globalGameEngine->addFireBall(fireball5);*/
		}
		setYVelocity(0.f);
		setYPosition(getBoundary().x);
	}
	else if (phase == ENTER_PHASE && getPosition().y >= getBoundary().y) {
		phase = WAIT_PHASE;
		orientation = DOWN;
		setYVelocity(0.f);
		setYPosition(getBoundary().y);
	}
	else if (timer >= WAIT_TIME && phase == WAIT_PHASE) {
		setYVelocity(-SPEED);
		phase = EXIT_PHASE;
		if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) setAnimation(firePiranhaRest);
		timer = 0.f;
	}
	else if (timer >= ATTACK_TIME && phase == ATTACK_PHASE) {
		setYVelocity(SPEED);
		phase = ENTER_PHASE;
		if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) setAnimation(firePiranhaRest);
		timer = 0.f;
	}

	if (getVelocity().y == 0.f) {
		timer += deltaTime;
	}
}

void Plant::draw(float deltaTime) {
	if (currentAnimation == nullptr) return;
	setXPosition(getPosition().x + velocity.x * deltaTime);
	setYPosition(getPosition().y + velocity.y * deltaTime);
	updateTime(deltaTime);
	if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) {
		int frame = 0;
		setDirection();
		if (direction == DOWNLEFT) frame = 0;
		if (direction == UPLEFT) frame = 1;
		if (direction == DOWNRIGHT) frame = 2;
		if (direction == UPRIGHT) frame = 3;

		currentAnimation->update(deltaTime);
		currentAnimation->render(getPosition(), frame);
	}
	else if (type == GREEN_PIRANHA || type == RED_PIRANHA) {
		currentAnimation->update(deltaTime);
		currentAnimation->render(getPosition());
	}
}

Vector2 Plant::getCentral() {
	float halfWidth = getWidth() / 2;
	return Vector2(getPosition().x + halfWidth, getPosition().y + halfWidth);
}

void Plant::setPlayerForFireball(Character* player) {
	this->player = player;
}

void Plant::setDirection() {
	Vector2 plantCentral = getCentral();
	Vector2 playerCentral = Vector2(player->getCenterX(), player->getCenterY());

	if (playerCentral.x < plantCentral.x && playerCentral.y < plantCentral.y) direction = UPLEFT;
	else if (playerCentral.x < plantCentral.x && playerCentral.y > plantCentral.y) direction = DOWNLEFT;
	else if (playerCentral.x > plantCentral.x && playerCentral.y < plantCentral.y) direction = UPRIGHT;
	else if (playerCentral.x > plantCentral.x && playerCentral.y > plantCentral.y) direction = DOWNRIGHT;
}