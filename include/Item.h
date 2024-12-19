#pragma once
#include"Sprite.h"

class Item : public Sprite {
private:
	int point;
public:
	Item() = default;
	Item(int point);

	int getPoint() const;
	virtual EntityType getType() const override;
	virtual ItemType getItemType() const = 0;
};

