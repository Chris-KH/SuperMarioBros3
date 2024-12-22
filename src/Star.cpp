#include "../include/Star.h"

Star::Star(StarType type, Vector2 position, Orientation orientation) : Item(POINT) {
	this->type = type;
	this->orientation = orientation;

	if (type == YELLOW_STAR) {
		starAnimation = RESOURCE_MANAGER.getAnimation("yellow_star_item")->clone();
	}
	else if (type == BLUE_STAR) {
		starAnimation = RESOURCE_MANAGER.getAnimation("blue_star_item")->clone();
	}

	setAnimation(starAnimation);
	setPosition(position);
}

void Star::update(float deltaTime) {
	if (isDead()) return;

	if (getOrientation() == RIGHT) {
		setXVelocity(SPEED);
	}
	else {
		setXVelocity(-SPEED);
	}

	if (gravityAvailable) {
		setYVelocity(getVelocity().y + GRAVITY * deltaTime);
	}
}

const StarType& Star::getStarType() const {
	return type;
}

ItemType Star::getItemType() const {
	return STAR;
}