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
	TextEffect(string text, Vector2 center, float duration, float delay = 0.f) {
		this->text = text;
		this->duration = duration;
		this->delay = delay;

		Font* myFont = RESOURCE_MANAGER.getFont("HolenVintage.otf");
		Vector2 textSize = MeasureTextEx(*myFont, text.c_str(), FONT_SIZE, 0.f);
		setSize(textSize);
		setCenter(center);
		
		outlineColor = BLANK;
		textColor = BLACK;

		setGravityAvailable(false);
		setCollisionAvailable(false);
		setVelocity({ 0.f, -TEXT_SPEED });
	}

	void setOutlineColor(Color color) {
		this->outlineColor = color;
	}

	void setTextColor(Color color) {
		this->textColor = color;
	}

	void update(float deltaTIme) override {
		if (isDead) return;

		duration -= deltaTIme;

		if (duration <= 0.f) {
			destroySprite();
		}
		setYVelocity(getVelocity().y + GRAVITY * deltaTIme);
	}

	void draw(float deltaTime = GetFrameTime()) override {
		if (isDead) return;

		setYPosition(getPosition().y + getVelocity().y * deltaTime);
		
		Font* myFont = RESOURCE_MANAGER.getFont("HolenVintage.otf");

		DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y + 2 }, FONT_SIZE, 0.f, outlineColor);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y - 2 }, FONT_SIZE, 0.f, outlineColor);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x + 2, getPosition().y}, FONT_SIZE, 0.f, outlineColor);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x - 2, getPosition().y}, FONT_SIZE, 0.f, outlineColor);

		DrawTextEx(*myFont, text.c_str(), getPosition(), FONT_SIZE, 0.f, textColor);
	}
};