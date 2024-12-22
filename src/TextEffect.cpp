#include"../include/TextEffect.h"

TextEffect::TextEffect(string text, Vector2 center, float duration, float delay) {
	this->text = text;
	this->duration = duration;
	this->delay = delay;

	Font* myFont = RESOURCE_MANAGER.getFont("WinterMinie.ttf");
	Vector2 textSize = MeasureTextEx(*myFont, text.c_str(), FONT_SIZE, OUTLINE_SIZE);
	setSize(textSize);
	setCenter(center);

	outlineColor = WHITE;
	textColor = BLACK;

	setVelocity({ 0.f, -TEXT_SPEED });
}

void TextEffect::setOutlineColor(Color color) {
	this->outlineColor = color;
}

void TextEffect::setTextColor(Color color) {
	this->textColor = color;
}

void TextEffect::draw(float deltaTime) {
	setYPosition(getPosition().y + getVelocity().y * deltaTime);

	Font* myFont = RESOURCE_MANAGER.getFont("WinterMinie.ttf");
	SetTextureFilter(myFont->texture, TEXTURE_FILTER_BILINEAR);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y + OUTLINE_SIZE }, FONT_SIZE, OUTLINE_SIZE, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x, getPosition().y - OUTLINE_SIZE }, FONT_SIZE, OUTLINE_SIZE, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x + OUTLINE_SIZE, getPosition().y }, FONT_SIZE, OUTLINE_SIZE, outlineColor);
	DrawTextEx(*myFont, text.c_str(), { getPosition().x - OUTLINE_SIZE, getPosition().y }, FONT_SIZE, OUTLINE_SIZE, outlineColor);

	DrawTextEx(*myFont, text.c_str(), getPosition(), FONT_SIZE, OUTLINE_SIZE, textColor);
}