#include "../include/Animation.h"
#include"../include/Background.h"

Background::Background(const Texture& texture, Animation* animation, BackgroundTiling tilingMode) 
	: texture(texture),
	backgroundAnimation(animation),
	tilingMode(tilingMode)
{}

Background::~Background() {
	delete backgroundAnimation;
}

const Animation& Background::getAnimation() const {
	return *backgroundAnimation;
}

const Texture& Background::getTexture() const {
	return texture;
}

BackgroundTiling Background::getTiling() const {
	return tilingMode;
}
