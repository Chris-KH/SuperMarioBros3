#pragma once
#include"Effect.h"

class TextEffect : public Effect {
private:
	string text;
	Color outlineColor;
	Color textColor;

	const float TEXT_DURATION = .5f; 
	const float TEXT_SPEED = 200.f;
	const float FONT_SIZE = 16.f;
public:
	TextEffect(string text, Vector2 center, float duration, float delay = 0.f);

	void setOutlineColor(Color color);
	void setTextColor(Color color);

	void update(float deltaTIme) override;
	void draw(float deltaTime = GetFrameTime()) override;
};