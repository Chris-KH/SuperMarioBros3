#ifndef COIN_H
#define COIN_H
#include "Item.h"

class GameEngine;

class Coin : public Item {
private:
	float BLOCK_COIN_LIFE_TIME = 0.5f;
	static constexpr int POINT = 100;
	static constexpr float COIN_UP_VELOCITY = 100.f;
	CoinType type;
	Animation* coinAnimation;
	float lifeTime;
public:
	Coin(CoinType type = STATIC_COIN, Vector2 position = { 0.f, 0.f });

	~Coin();

	const CoinType& getCoinType() const;

	ItemType getItemType() const override;

	void update(float deltaTime) override;
};
#endif