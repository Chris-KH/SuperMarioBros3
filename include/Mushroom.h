#pragma once
#include "Item.h"

class Mushroom : public Item {
private:
	MushroomType type;
public:
	const int POINT = 1000;
	const float SPEED = 70.f;
 
	//Create new mushroom
	Mushroom(MushroomType type = MUSHROOM_SUPER);

	//Get type of mush room
	MushroomType getItemType() const;
};