#include "../include/Mushroom.h"

Mushroom::Mushroom(MushroomType type, Vector2 position) : Item(type == MUSHROOM_SUPER ? POINT : 0) {
	this->type = type;
	setPosition(position);

	if (type == MUSHROOM_SUPER) {
		setAnimation("red_mushroom_item");
	}
	else if (type == MUSHROOM_1UP) {
		setAnimation("green_mushroom_item");
	}

	setXVelocity(SPEED);
}

const MushroomType& Mushroom::getMushroomType() const {
	return this->type;
}