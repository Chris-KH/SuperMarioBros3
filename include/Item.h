#ifndef ITEM_H
#define ITEM_H

#include"Sprite.h"

class Item : public Sprite {
private:
	int point;
public:
	Item(int point = 0);

	int getPoint() const;
	virtual EntityType getType() const override;
	virtual ItemType getItemType() const = 0;

	virtual void update(float deltaTime) override = 0;
};

#endif //ITEM_H
