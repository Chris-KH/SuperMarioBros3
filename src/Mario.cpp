#include "../include/Mario.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarmanState.h"

Mario::Mario(Vector2 pos) : Character(pos) {
	state = new FireState;
	state->setState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x, this->getPosition().y));
};

CharacterType Mario::getCharacterType() const {
	return CharacterType::MARIO;
}

void Mario::update(float deltaTime) {
	INPUT_MANAGER.update();
	state->update(this, deltaTime);
	currentAnimation->update(deltaTime);
}

void Mario::onKey(KeyboardKey key, bool pressed) {
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

void Mario::reset() {
	Character::reset();
}