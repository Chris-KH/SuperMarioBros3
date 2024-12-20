#include "../include/Plant.h"
#include "../include/Character.h"
#include "../include/Fireball.h"

Plant::~Plant() {
	free(piranha);
	free(firePiranhaRest);
	free(firePiranhaAttack);
	piranha = nullptr;
	firePiranhaRest = nullptr;
	firePiranhaAttack = nullptr;
}

Plant::Plant(PlantType type, Vector2 center, Character* player) {
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

	setCenter(center);
}

EnemyType Plant::getEnemyType() const {
	return EnemyType::PLANT;
}

void Plant::update(float deltaTime) {
	if (isDead) return;
	
	if (phase == EXIT_PHASE && getPosition().y <= getBoundary().x) {
		phase = ATTACK_PHASE;
		orientation = UP;
		if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) {
			setAnimation(firePiranhaAttack);
			//Create a Fireball
		}
		setYVelocity(0.f);
		setYPosition(getBoundary().x);
	}
	else if (phase == ENTER_PHASE && getPosition().y >= getBoundary().y) {
		phase = WAIT_PHASE;
		orientation = DOWN;
		if (type == GREEN_FIREPIRANHA || type == RED_FIREPIRANHA) setAnimation(firePiranhaRest);
		setYVelocity(0.f);
		setYPosition(getBoundary().y);
	}
	else if (timer >= WAIT_TIME && phase == WAIT_PHASE) {
		setYVelocity(-SPEED);
		phase = EXIT_PHASE;
		timer = 0.f;
	}
	else if (timer >= ATTACK_TIME && phase == ATTACK_PHASE) {
		setYVelocity(SPEED);
		phase = ENTER_PHASE;
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
	float halfWidth = getSize().x;
	return Vector2(getPosition().x + halfWidth, getPosition().y + halfWidth);
}

void Plant::setDirection() {
	Vector2 plantCentral = getCentral();
	Vector2 playerCentral = Vector2(player->getCenterX(), player->getCenterY());

	if (playerCentral.x < plantCentral.x && playerCentral.y < plantCentral.y) direction = UPLEFT;
	else if (playerCentral.x < plantCentral.x && playerCentral.y > plantCentral.y) direction = DOWNLEFT;
	else if (playerCentral.x > plantCentral.x && playerCentral.y < plantCentral.y) direction = UPRIGHT;
	else if (playerCentral.x > plantCentral.x && playerCentral.y > plantCentral.y) direction = DOWNRIGHT;
}