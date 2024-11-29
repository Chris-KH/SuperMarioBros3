#pragma once
#include"Sprite.h"

class Item : public Sprite {
private:

public:

	virtual EntityType getType() const override { return EntityType::ITEM; }
};

