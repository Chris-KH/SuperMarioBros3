#include "../include/Item.h"

Item::Item(int point) {
	this->point = point;
}

EntityType Item::getType() const { return EntityType::ITEM; }

const int& Item::getPoint() const {
	return this->point;
}