#include"../include/Effect.h"

Effect::~Effect() {
	free(currentAnimation);
	currentAnimation = nullptr;
}

Effect::Effect(Animation* animation, Vector2 position, float duration, float delay) : Sprite(position) {
	currentAnimation = animation;
	this->duration = duration;
	this->delay = delay;
	this->destroyWhenFinish = true;
	setCollisionAvailable(false);
}

Effect::Effect(Animation* animation, Vector2 position, bool destroyWhenFinish, float delay) : Sprite(position) {
	currentAnimation = animation;
	if (destroyWhenFinish == true) {
		this->duration = currentAnimation->getAnimationTime();
	}
	else this->duration = 0.f;
	this->delay = delay;
	this->destroyWhenFinish = destroyWhenFinish;
	setCollisionAvailable(false);
}

EntityType Effect::getType() const {
	return EFFECT;
}

void Effect::update(float deltaTime) {
	if (isDead()) return;

	if (duration <= 0.f) {
		killEntity();
	}

	if (isGravityAvailable()) setYVelocity(getVelocity().y + GRAVITY * deltaTime);

	duration -= deltaTime;
}