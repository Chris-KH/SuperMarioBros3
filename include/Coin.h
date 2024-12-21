#pragma once
#include "Item.h"

class Coin : public Item {
private:
	CoinType type;
	Animation* coinAnimation;
public:
	const int POINT = 100;
	const float COIN_UP_VELOCITY = 200.f;
	
	Coin(CoinType type = STATIC_COIN, Vector2 position = {0.f, 0.f}) : Item(POINT) {
		this->type = type;
		
		coinAnimation = RESOURCE_MANAGER.getAnimation("coin_item")->clone();

		if (type == BLOCK_COIN) {
			setYVelocity(-COIN_UP_VELOCITY);
		}

		setPosition(position);
		setAnimation(coinAnimation);
		setGravityAvailable(false);
	}

	~Coin() {
		free(coinAnimation);
		coinAnimation = nullptr;
	}

	const CoinType& getCoinType() const {
		return type;
	}

	ItemType getItemType() const override {
		return COIN;
	}

	void update(float deltaTime) override {
		if (isDead()) return;
		if (gravityAvailable) {
			setYVelocity(getVelocity().y + GRAVITY * deltaTime);
		}
	}
};

