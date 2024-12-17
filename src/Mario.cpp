#include "../include/Mario.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarState.h"

Mario::Mario(Vector2 pos, Vector2 size, Color col) : Character(pos, size, col) {
	state = new NormalState;
	state->setState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x, this->getPosition().y));
};

Character::CHACRACTER Mario::getCharacterType() const {
	return CHACRACTER::MARIO;
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