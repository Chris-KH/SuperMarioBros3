#include "../include/StarmanState.h"

void StarmanState::setState(Character* character) {
    if (character == nullptr) {
        return; // Avoid dereferencing a null pointer
    }

    if (character->getCharacterType() == MARIO) {

    }
    else if (character->getCharacterType() == LUIGI) {

    }
}

void StarmanState::update(Character* character, float deltaTime) {

};

STATE StarmanState::getState() const {
    return STATE::STARMAN;
}