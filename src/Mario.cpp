#include "../include/Mario.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Mario::Mario(Vector2 pos) : Character(pos) {
	state = new NormalState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	Vector2 vector2Pos = {this->getPosition().x, this->getPosition().y};
	this->setPosition(vector2Pos);
};

CharacterType Mario::getCharacterType() const {
	return CharacterType::MARIO;
}

void Mario::reset() {
	Character::reset();
}