#include"../include/InputManager.h"

void InputManager::bindKey(KeyboardKey key) {
    // Ensure the key is initialized in the map
    if (keyStates.find(key) == keyStates.end()) {
        keyStates[key] = false; // Default state: not pressed
    }
}

void InputManager::addListener(InputManager::Listener& listener) {
    if (find_if(listeners.begin(), listeners.end(), [&listener](Listener* l) { return l == &listener; }) == listeners.end()) {
        listeners.push_back(&listener);
    }
}

void InputManager::removeListener(InputManager::Listener& listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), &listener), listeners.end());
}

void InputManager::update() {
    if (keyStates.empty()) return;

    for (auto& [key, state] : keyStates) {
        bool isPressed = IsKeyDown(key);
        // If state has changed, notify listeners
        if (isPressed != state) {
            state = isPressed; // Update stored state
            for (auto listener : listeners) {
                if (listener) {
                    listener->onKey(key, isPressed);
                }
            }
        }
    }
}