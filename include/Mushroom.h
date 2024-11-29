#pragma once
#include "Item.h"

enum MushroomType{
	MUSHROOM_SUPER, //Enlarges Mario, turning him into Super Mario and allowing him to survive one hit.
	MUSHROOM_1UP //Provides an extra life.
};

//class Mushroom : public Item {
//private:
//	MushroomType type;
//public:
//	static constexpr float SPEED = 0.f;
// 
//	//Create new mushroom
//	Mushroom(MushroomType type = MUSHROOM_SUPER);
//
//	//Get type of mush room
//	MushroomType getType() const;
//};
//
//Mushroom::Mushroom(MushroomType type = MUSHROOM_SUPER) {
//
//}
//
//MushroomType Mushroom::getType() const {
//	return this->type;
//}