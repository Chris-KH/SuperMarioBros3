#ifndef FLOWER_H
#define FLOWER_H

#include "Item.h"

class Flower : public Item {
private:
	const int POINT = 1000;

	FlowerType type;
	Animation* flowerAniamtion;

	const float APPEAR_SPEED = 16.f;
public:
	Flower(FlowerType type = FIRE_FLOWER, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);

	~Flower();

	const FlowerType& getFlowerType() const;

	ItemType getItemType() const override;

	void update(float deltaTime) override;
};

#endif // !FLOWER_H