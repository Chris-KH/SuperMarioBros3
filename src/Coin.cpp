#include "../include/Coin.h"

Coin::Coin() : Item(POINT) {
	setAnimation("coin_item");
	setGravityAvailable(false);
}