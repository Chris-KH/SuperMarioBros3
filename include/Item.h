#ifndef ITEM_H
#define ITEM_H

#include"Sprite.h"

class Item : public Sprite {
private:
	int point;
	bool appear;
	float bottomAppear;
public:
	Item(int point = 0);

	const int& getPoint() const;
	virtual EntityType getType() const override;
	virtual ItemType getItemType() const = 0;

	virtual void update(float deltaTime) override = 0;
	virtual void setAppearBottom(float bottom);
	virtual const float& getAppearBottom();

	virtual void setAppear(bool appear);
	virtual bool isAppear() const;
};

#endif
