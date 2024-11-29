#pragma once
#include "Item.h"

enum MushroomType{
	MUSHROOM_SUPER,
	MUSHROOM_1UP
};

//class Mushroom : public Item {
//private:
//	MushroomType type;
//public:
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