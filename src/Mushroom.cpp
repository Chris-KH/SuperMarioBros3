#include "../include/Mushroom.h"

Mushroom::Mushroom(MushroomType type, Vector2 position, Orientation orientation) : Item(type == MUSHROOM_SUPER ? POINT : 0) {
	this->type = type;
	this->orientation = orientation;

	if (type == MUSHROOM_SUPER) {
		mushroomAnimation = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/miscellaneous.txt/super_mushroom_item")->clone();
	}
	else if (type == MUSHROOM_1UP) {
		mushroomAnimation = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/miscellaneous.txt/1up_mushroom_item")->clone();
	}

	setAnimation(mushroomAnimation);
	setPosition(position);
	setCollisionAvailable(false);
	RESOURCE_MANAGER.playSound("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Sound/mushroom_appears.wav");
}

Mushroom::~Mushroom() {
	free(mushroomAnimation);
	mushroomAnimation = nullptr;
}

const MushroomType& Mushroom::getMushroomType() const {
	return this->type;
}

ItemType Mushroom::getItemType() const {
	return MUSHROOM;
}

void Mushroom::update(float deltaTime) {
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