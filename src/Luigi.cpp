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
	Vector2 vector2Pos = {this->getPosition().x,this->getPosition().y};
	this->setPosition(vector2Pos);
};

CharacterType Luigi::getCharacterType() const  {
	return CharacterType::LUIGI;
}

void Luigi::onKey(KeyboardKey key, bool pressed) {
	if (isDead()) return;

	if (key == KEY_R) {

	}
}

void Luigi::reset() {
	Character::reset();
}