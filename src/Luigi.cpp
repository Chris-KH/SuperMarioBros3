#include"../include/Luigi.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"

Luigi::Luigi(Vector2 pos) : Character(pos) {
	state = new NormalState;
	state->setState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	Vector2 vector2 = {this->getPosition().x,this->getPosition().y};
	this->setPosition(vector2);
};

CharacterType Luigi::getCharacterType() const  {
	return CharacterType::LUIGI;
}

void Luigi::update(float deltaTime) {
	INPUT_MANAGER.update();
	state->update(this, deltaTime);
	currentAnimation->update(deltaTime);
}

void Luigi::onKey(KeyboardKey key, bool pressed) {
	if (isDead()) return;

	if (key == KEY_SPACE) {
		if (pressed && !isJumping()) {
			
		}
	}
	else if (key == KEY_S) {
		if (pressed) {
			sitting = true;
		}
		else sitting = false;
	}
}

void Luigi::reset() {
	Character::reset();
}