#ifndef EFFECT_H
#define EFFECT_H
#include"Sprite.h"

class Effect : public Sprite {
protected:
	float duration;
	float delay;
	bool destroyWhenFinish;
public:
	virtual ~Effect();
	Effect() = default;
	Effect(Animation* animation, Vector2 position = { 0.f, 0.f }, float duration = 0.f, float delay = 0.f);

	Effect(Animation* animation, Vector2 position = { 0.f, 0.f }, bool destroyWhenFinish = true, float delay = 0.f);

	virtual EntityType getType() const;

	virtual void update(float deltaTime) override;
};
#endif