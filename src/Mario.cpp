#include "../include/Mario.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Mario::Mario(Vector2 pos) : Character(pos) {
	state = new SuperState(this);
	lastState = state->getState();
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x, this->getPosition().y));
};

CharacterType Mario::getCharacterType() const {
	return CharacterType::MARIO;
}

void Mario::onKey(KeyboardKey key, bool pressed) {
	if (isDead()) return;

	if (key == KEY_R) {
		
	}
}

void Mario::reset() {
	Character::reset();
}