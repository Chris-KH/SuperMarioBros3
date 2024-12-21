#pragma once
#include"Sprite.h"

class Effect : public Sprite {
protected:
	float duration;
	float delay;
	bool destroyWhenFinish;
public:
	virtual ~Effect() {
		free(currentAnimation);
		currentAnimation = nullptr;
	}
	Effect() = default;
	Effect(Animation* animation, Vector2 position = {0.f, 0.f}, float duration = 0.f, float delay = 0.f) : Sprite(position) {
		currentAnimation = animation;
		this->duration = duration;
		this->delay = delay;
		this->destroyWhenFinish = true;
		setGravityAvailable(false);
		setCollisionAvailable(false);
	}

	Effect(Animation* animation, Vector2 position = { 0.f, 0.f }, bool destroyWhenFinish = true, float delay = 0.f) {
		currentAnimation = animation;
		if (destroyWhenFinish == true) {
			this->duration = currentAnimation->getAnimationTime();
		}
		else this->duration = 0.f;
		this->delay = delay;
		this->destroyWhenFinish = destroyWhenFinish;
		setGravityAvailable(false);
		setCollisionAvailable(false);
	}

	virtual EntityType getType() const {
		return EFFECT;
	}

	virtual void draw(float deltaTime = GetFrameTime())  override {

	}

	virtual void update(float deltaTime)  override {

	}
};