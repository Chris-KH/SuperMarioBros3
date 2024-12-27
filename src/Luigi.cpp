#include"../include/Luigi.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"
#include"../include/SuperStarmanState.h"
#include"../include/FireStarmanState.h"

Luigi::Luigi(Vector2 pos) : Character(pos) {
	state = new NormalState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	Vector2 vector2 = {this->getPosition().x,this->getPosition().y};
	this->setPosition(vector2);
};

CharacterType Luigi::getCharacterType() const  {
	return CharacterType::LUIGI;
}

void Luigi::reset() {
	Character::reset();
}