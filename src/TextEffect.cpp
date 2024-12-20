#include"../include/TextEffect.h"

TextEffect::TextEffect(string text, Vector2 center, float duration, float delay) {
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

void TextEffect::setOutlineColor(Color color) {
	this->outlineColor = color;
}

void TextEffect::setTextColor(Color color) {
	this->textColor = color;
}

void TextEffect::update(float deltaTIme) {
	if (isDead()) return;

	duration -= deltaTIme;

	if (duration <= 0.f) {
		killEntity();
	}
	setYVelocity(getVelocity().y + GRAVITY * deltaTIme);
}

void TextEffect::draw(float deltaTime) {
	if (isDead()) return;

	setYPosition(getPosition().y + getVelocity().y * deltaTime);

	Font* myFont = RESOURCE_MANAGER.getFont("HolenVintage.otf");

	DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y + 2 }, FONT_SIZE, 0.f, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y - 2 }, FONT_SIZE, 0.f, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x + 2, getPosition().y }, FONT_SIZE, 0.f, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x - 2, getPosition().y }, FONT_SIZE, 0.f, outlineColor);

	DrawTextEx(*myFont, text.c_str(), getPosition(), FONT_SIZE, 0.f, textColor);
}