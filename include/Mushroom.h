#pragma once
#include "Item.h"

class Mushroom : public Item {
private:
	MushroomType type;
public:
	const int POINT = 1000;
	const float SPEED = 70.f;
 
	//Create new mushroom
	Mushroom(MushroomType type = MUSHROOM_SUPER, Vector2 position = {0.f, 0.f});

	//Get type of mush room
	const MushroomType& getMushroomType() const;
	ItemType getItemType() const override {
		return MUSHROOM;
	}
};