#include "../include/Flower.h"

Flower::Flower(FlowerType type, Vector2 position, Orientation orientation) : Item(POINT) {
	this->type = type;

	flowerAniamtion = nullptr;
	if (type == FIRE_FLOWER) {
		flowerAniamtion = RESOURCE_MANAGER.getAnimation("assets/Animation/miscellaneous.txt/fire_flower_item")->clone();
	}
	
	setCollisionAvailable(false);
	setYVelocity(0.f);
	setAnimation(flowerAniamtion);
	setPosition(position);
}

Flower::~Flower() {
	free(flowerAniamtion);
	flowerAniamtion = nullptr;
}

const FlowerType& Flower::getFlowerType() const {
	return type;
}

ItemType Flower::getItemType() const  {
	return FLOWER;
}

void Flower::update(float deltaTime)  {
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
}