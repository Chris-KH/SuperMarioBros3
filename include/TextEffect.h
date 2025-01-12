#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include"Effect.h"

class TextEffect : public Effect {
private:
	string text;
	Color outlineColor;
	Color textColor;

	static constexpr float TEXT_DURATION = .5f;
	const float TEXT_SPEED = 400.f;
	static constexpr float FONT_SIZE = 14.f;
	static constexpr float OUTLINE_SIZE = FONT_SIZE / 20.f;
public:
	TextEffect(string text, Vector2 center, float duration = TEXT_DURATION, float delay = 0.f);

	void setOutlineColor(Color color);
	void setTextColor(Color color);

	void draw(float deltaTime = GetFrameTime()) override;
};
#endif