#include "../include/Mario.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Mario::Mario(Vector2 pos) : Character(pos) {
	state = new FireStarmanState;
	state->setState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x, this->getPosition().y));
};

CharacterType Mario::getCharacterType() const {
	return CharacterType::MARIO;
}

void Mario::update(float deltaTime) {
	if (isDead()) return;

	if (phase == DEFAULT_PHASE) {
		INPUT_MANAGER.update();
		state->update(this, deltaTime);
	}
	else if (phase == TRANSFORM_PHASE) {
		//transform
	}
	else if (phase == DEAD_PHASE) {
		//dead
	}
	else if (phase == EXIT_PHASE) {
		//exit
	}
	else if (phase == ENTER_PHASE) {
		//enter
	}
}

void Mario::onKey(KeyboardKey key, bool pressed) {
	if (isDead()) return;

	if (key == KEY_R) {
		
	}
}

void Mario::reset() {
	Character::reset();
}