#include"../include/Luigi.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Luigi::Luigi(Vector2 pos) : Character(pos) {
	state = new NormalState(this);
	lastState = state->getState();
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x,this->getPosition().y));
};

CharacterType Luigi::getCharacterType() const  {
	return CharacterType::LUIGI;
}

void Luigi::update(float deltaTime) {
	if (isDead()) return;
	if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
		if (!isInvicible()) {
			invicibleTime = 0.f;
			transform(lastState);
		}
	}

	if (phase == DEFAULT_PHASE) {
		INPUT_MANAGER.update();
		state->update(deltaTime);
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

	if (state->getState() == STARMAN || state->getState() == SUPERSTARMAN || state->getState() == FIRESTARMAN) {
		if (isInvicible()) {
			invicibleTime -= deltaTime;
		}
	}
}

void Luigi::onKey(KeyboardKey key, bool pressed) {
	if (isDead()) return;

	if (key == KEY_R) {

	}
}

void Luigi::reset() {
	Character::reset();
}