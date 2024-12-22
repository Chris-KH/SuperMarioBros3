#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "Item.h"

class Mushroom : public Item {
private:
	MushroomType type;
	Animation* mushroomAnimation;
public:
	const int POINT = 1000;
	const float SPEED = 70.f;
 
	//Create new mushroom
	Mushroom(MushroomType type = MUSHROOM_SUPER, Vector2 position = {0.f, 0.f}, Orientation orientation = RIGHT);
	~Mushroom();

	//Get type of mush room
	const MushroomType& getMushroomType() const;
	ItemType getItemType() const override;

	void update(float deltaTime) override;
};

#endif // !MUSHROOM_H