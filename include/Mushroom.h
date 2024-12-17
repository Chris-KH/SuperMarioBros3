#pragma once
#include "Item.h"

enum MushroomType{
	MUSHROOM_SUPER, //Enlarges Mario, turning him into Super Mario and allowing him to survive one hit.
	MUSHROOM_1UP //Provides an extra life.
};

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