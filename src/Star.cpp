#include "../include/Star.h"

Star::Star(StarType type, Vector2 position, Orientation orientation) : Item(POINT) {
	this->type = type;
	this->orientation = orientation;

	if (type == YELLOW_STAR) {
		starAnimation = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/miscellaneous.txt/yellow_star_item")->clone();
	}
	else if (type == BLUE_STAR) {
		starAnimation = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/miscellaneous.txt/blue_star_item")->clone();
	}
	
	setAnimation(starAnimation);
	setPosition(position);
	setCollisionAvailable(false);
}

void Star::update(float deltaTime) {
	Sprite::update(deltaTime);

	if (isDead()) return;

	if (isAppear()) {
		if (getBottom() <= getAppearBottom()) {
			setYPosition(getAppearBottom() - getSize().y);
			setAppear(false);
			setYVelocity(0.f);
			setCollisionAvailable(true);
			return;
		}
		setYVelocity(-APPEAR_SPEED);
	}
	else {
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
}

const StarType& Star::getStarType() const {
	return type;
}

ItemType Star::getItemType() const {
	return STAR;
}