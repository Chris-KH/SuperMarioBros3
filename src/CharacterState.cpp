#include "../include/CharacterState.h"

CharacterState::CharacterState(Character* character ) {
	this->character = character;
}

void CharacterState::setCharacter(Character* character) {
	this->character = character;
}

Character* CharacterState::getCharacter() const {
	return character;
}