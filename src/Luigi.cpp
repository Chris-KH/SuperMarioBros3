#include"../include/Luigi.h"
#include"../include/NormalState.h"
#include"../include/SuperState.h"
#include"../include/FireState.h"
#include"../include/StarState.h"

Luigi::Luigi(Vector2 pos, Vector2 size, Color col) : Character(pos, size, col) {
	state = new NormalState;
	state->setState(this);
	setAnimation(idleRight);
	INPUT_MANAGER.addListener(*this);
	this->setPosition(Vector2(this->getPosition().x,this->getPosition().y));
};

Character::CHACRACTER Luigi::getCharacterType() const  {
	return CHACRACTER::LUIGI;
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
	else if (key == KEY_D) {
		if (pressed) {
			orientation = true;
		}
	}
	else if (key == KEY_A) {
		if (pressed) {
			orientation = false;
		}
	}
}

void Luigi::reset() {
	Character::reset();
}