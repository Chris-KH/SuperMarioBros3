#include "../include/Coin.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"

Coin::Coin(CoinType type, Vector2 position) : Item(POINT) {
	this->type = type;
	this->lifeTime = 0.f;
	coinAnimation = RESOURCE_MANAGER.getAnimation("../../assets/Animation/tiles1.txt/coin_item")->clone();

	if (type == BLOCK_COIN) {
		setYVelocity(-COIN_UP_VELOCITY);
		setCollisionAvailable(false);
		this->lifeTime = BLOCK_COIN_LIFE_TIME;
		RESOURCE_MANAGER.playSound("../../assets/Sound/coin.wav");
	}

	setPosition(position);
	setAnimation(coinAnimation);
	setGravityAvailable(false);
}

Coin::~Coin() {
	free(coinAnimation);
	coinAnimation = nullptr;
}

const CoinType& Coin::getCoinType() const {
	return type;
}

ItemType Coin::getItemType() const {
	return COIN;
}

void Coin::update(float deltaTime) {
	Sprite::update(deltaTime);

	if (isDead()) return;
	if (gravityAvailable) {
		setYVelocity(getVelocity().y + GRAVITY * deltaTime);
	}

	if (type == BLOCK_COIN) {
		if (lifeTime <= 0.f) {
			killEntity();
			Effect* text = new TextEffect(to_string(POINT).c_str(), getCenter());
			text->setYVelocity(0.f);
			globalGameEngine->addEffect(text);
		}

		lifeTime -= deltaTime;
	}
}