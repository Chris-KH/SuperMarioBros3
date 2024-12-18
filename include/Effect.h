#pragma once
#include"Sprite.h"

class Effect : public Sprite {
protected:
	Animation* effect;
	float duration;
	float delay;
	bool destroyWhenFinish;
public:
	virtual ~Effect() {
		free(effect);
		effect = nullptr;
	}
	Effect() = default;
	Effect(Animation* animation, Vector2 position = {0.f, 0.f}, float duration = 0.f, float delay = 0.f) : Sprite(position) {
		effect = animation;
		this->duration = duration;
		this->delay = delay;
		this->destroyWhenFinish = true;
	}

	Effect(Animation* animation, Vector2 position = { 0.f, 0.f }, bool destroyWhenFinish = true, float delay = 0.f) {
		effect = animation;
		if (destroyWhenFinish == true) {
			this->duration = effect->getAnimationTime();
		}
		else this->duration = 0.f;
		this->delay = delay;
		this->destroyWhenFinish = destroyWhenFinish;
	}

	virtual EntityType getType() const {
		return EFFECT;
	}

	virtual void draw(float deltaTime = GetFrameTime()) {

	}

	virtual void update(float deltaTime) {

	}
};