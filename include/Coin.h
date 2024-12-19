#pragma once
#include "Item.h"

class Coin : public Item {
private:
	CoinType type;
public:
	const int POINT = 100;
	
	Coin(CoinType = STATIC_COIN, Vector2 position = {0.f, 0.f});

	ItemType getItemType() const override {
		return COIN;
	}
};

