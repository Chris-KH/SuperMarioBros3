#include "../include/Mushroom.h"

Mushroom::Mushroom(MushroomType type) : Item(type == MUSHROOM_SUPER ? POINT : 0) {
	this->type = type;

	if (type == MUSHROOM_SUPER) {
		setAnimation("red_mushroom_item");
	}
	else if (type == MUSHROOM_1UP) {
		setAnimation("green_mushroom_item");
	}

	setXVelocity(SPEED);
}

MushroomType Mushroom::getItemType() const {
	return this->type;
}