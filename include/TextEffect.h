#pragma once
#include"Effect.h"

class TextEffect : public Effect {
private:
	string text;

	const float TEXT_DURATION = .5f; 
	const float TEXT_SPEED = 200.f;
	const float FONT_SIZE = 16.f;
public:
	TextEffect(string text, Vector2 center, float duration, float delay = 0.f) {
		effect = nullptr;
		this->text = text;
		this->duration = duration;
		this->delay = delay;

		Font* myFont = RESOURCE_MANAGER.getFont("HolenVintage.otf");
		Vector2 textSize = MeasureTextEx(*myFont, text.c_str(), FONT_SIZE, 0.f);
		setSize(textSize);
		setCenter(center);
		

		setGravityAvailable(false);
		setCollisionAvailable(false);
		setVelocity({ 0.f, -TEXT_SPEED });
	}

	void update(float deltaTIme) override {
		setYVelocity(getVelocity().y + GRAVITY * deltaTIme);

		duration -= deltaTIme;

		if (duration <= 0.f) {
			destroySprite();
		}
	}

	void draw(float deltaTime = GetFrameTime()) override {
		if (isDead) return;

		setYPosition(getPosition().y + getVelocity().y * deltaTime);
		
		Font* myFont = RESOURCE_MANAGER.getFont("HolenVintage.otf");

		DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y + 2 }, FONT_SIZE, 0.f, BLACK);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y - 2 }, FONT_SIZE, 0.f, BLACK);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x + 2, getPosition().y}, FONT_SIZE, 0.f, BLACK);
		DrawTextEx(*myFont, text.c_str(), { getPosition().x - 2, getPosition().y}, FONT_SIZE, 0.f, BLACK);

		DrawTextEx(*myFont, text.c_str(), getPosition(), FONT_SIZE, 0.f, WHITE);
	}
};