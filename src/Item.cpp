#include "../include/Item.h"

Item::Item(int point) {
	this->point = point;
	this->appear = true;
	this->bottomAppear = 0.f;
}

EntityType Item::getType() const { return EntityType::ITEM; }

const int& Item::getPoint() const {
	return this->point;
}

void Item::setAppearBottom(float bottom) {
	this->bottomAppear = bottom;
}

const float& Item::getAppearBottom() {
	return this->bottomAppear;
}

void Item::setAppear(bool appear) {
	this->appear = appear;
}

bool Item::isAppear() const {
	return this->appear;
}