#include "../include/Plant.h"
#include "../include/Character.h"

Plant::~Plant() {
	free(piranha);
	free(firePiranhaRest);
	free(firePiranhaAttack);
	piranha = nullptr;
	firePiranhaRest = nullptr;
	firePiranhaAttack = nullptr;
}

Plant::Plant(PlantType type, Vector2 position, Character* player) : Enemy(position) {
	this->type = type;
	setXVelocity(0.f);
	setYVelocity(0.f);
	setGravityAvailable(false);
	this->player = player;

	piranha = nullptr;
	firePiranhaRest = nullptr;
	firePiranhaAttack = nullptr;
	direction = UP;
	orientation = UP;

	if (type == GREEN_PIRANHA) {
		piranha = RESOURCE_MANAGER.getAnimation("green_piranha")->clone();
		setAnimation(piranha);
	}
	else if (type == GREEN_FIREPIRANHA) {
		firePiranhaRest = RESOURCE_MANAGER.getAnimation("green_firepiranha")->clone();
		firePiranhaAttack = RESOURCE_MANAGER.getAnimation("green_firepiranha_attack")->clone();
		setDirection();
		setAnimation(firePiranhaRest);
	}
}

EnemyType Plant::getEnemyType() const {
	return EnemyType::PLANT;
}

void Plant::update(float deltaTime) {
	setDirection();
}

void Plant::draw(float deltaTime) {
	if (currentAnimation == nullptr) return;
	setXPosition(getPosition().x + velocity.x * deltaTime);
	setYPosition(getPosition().y + velocity.y * deltaTime);
	if (type == GREEN_FIREPIRANHA) {
		int frame = 0;
		if (direction == DOWNLEFT) frame = 0;
		if (direction == UPLEFT) frame = 1;
		if (direction == DOWNRIGHT) frame = 2;
		if (direction == UPRIGHT) frame = 3;

		currentAnimation->render(getPosition(), frame);
	}
	else if (type == GREEN_PIRANHA) {
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