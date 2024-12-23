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
	this->setPosition(Vector2(this->getPosition().x, this->getPosition().y));
};

CharacterType Mario::getCharacterType() const {
	return CharacterType::MARIO;
}

void Mario::reset() {
	Character::reset();
}