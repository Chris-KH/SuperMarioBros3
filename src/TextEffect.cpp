#include"../include/TextEffect.h"

TextEffect::TextEffect(string text, Vector2 center, float duration, float delay) {
	this->text = text;
	this->duration = duration;
	this->delay = delay;

	//Font* myFont = RESOURCE_MANAGER.getFont("WinterMinie.ttf");
	Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), FONT_SIZE,  4 * OUTLINE_SIZE);
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

	Font* myFont = RESOURCE_MANAGER.getFont("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Font/WinterMinie.ttf");
	SetTextureFilter(myFont->texture, TEXTURE_FILTER_BILINEAR);
	DrawTextEx(GetFontDefault(), text.c_str(), { getPosition().x, getPosition().y + OUTLINE_SIZE }, FONT_SIZE, 4 * OUTLINE_SIZE, outlineColor);
	DrawTextEx(GetFontDefault(), text.c_str(), { getPosition().x, getPosition().y - OUTLINE_SIZE }, FONT_SIZE, 4 * OUTLINE_SIZE, outlineColor);
	DrawTextEx(GetFontDefault(), text.c_str(), { getPosition().x + OUTLINE_SIZE, getPosition().y }, FONT_SIZE, 4 * OUTLINE_SIZE, outlineColor);
	DrawTextEx(GetFontDefault(), text.c_str(), { getPosition().x - OUTLINE_SIZE, getPosition().y }, FONT_SIZE, 4 * OUTLINE_SIZE, outlineColor);

	DrawTextEx(GetFontDefault(), text.c_str(), getPosition(), FONT_SIZE, 4 * OUTLINE_SIZE, textColor);
}