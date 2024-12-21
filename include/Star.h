#pragma
#include "Item.h"

class Star : public Item {
private:
	StarType type;
	Animation* starAnimation;
public:
	const int POINT = 1000;
	const float SPEED = 70.f;

	Star(StarType type = YELLOW_STAR, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT) : Item(POINT) {
		this->type = type;
		this->orientation = orientation;

		if (type == YELLOW_STAR) {
			starAnimation = RESOURCE_MANAGER.getAnimation("yellow_star")->clone();
		}
		else if (type == BLUE_STAR) {
			starAnimation = RESOURCE_MANAGER.getAnimation("blue_star")->clone();
		}
		
		setAnimation(starAnimation);
		setPosition(position);
	}

	void update(float deltaTime) override {
		if (isDead()) return;

		if (getOrientation() == RIGHT) {
			setXVelocity(SPEED);
		}
		else {
			setXVelocity(-SPEED);
		}

		if (gravityAvailable) {
			setYVelocity(getVelocity().y + GRAVITY * deltaTime);
		}
	}

	const StarType& getStarType() const {
		return type;
	}

	ItemType getItemType() const override {
		return STAR;
	}
};