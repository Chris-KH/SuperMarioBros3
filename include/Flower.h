#ifndef FLOWER_H
#define FLOWER_H

#include "Item.h"

class Flower : public Item {
private:
	FlowerType type;
	Animation* flowerAniamtion;
public:
	const int POINT = 1000;

	Flower(FlowerType type = FIRE_FLOWER, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT) : Item(POINT) {
		this->type = type;

		flowerAniamtion = nullptr;
		if (type == FIRE_FLOWER) {
			flowerAniamtion = RESOURCE_MANAGER.getAnimation("fire_flower_item")->clone();
		}
		else if (type == ICE_FLOWER) {

		}

		setAnimation(flowerAniamtion);
		setPosition(position);
	}

	~Flower() {
		free(flowerAniamtion);
		flowerAniamtion = nullptr;
	}

	const FlowerType& getFlowerType() const {
		return type;
	}

	ItemType getItemType() const override {
		return FLOWER;
	}

	void update(float deltaTime) override {
		if (isDead()) return;
		
	}
};

#endif // !FLOWER_H