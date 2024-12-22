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

void Luigi::reset() {
	Character::reset();
}