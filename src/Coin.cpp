#include "../include/Coin.h"

Coin::Coin(CoinType type, Vector2 position) : Item(POINT) {
	this->type = type;
	setPosition(position);
	setAnimation("coin_item");
	setGravityAvailable(false);
}