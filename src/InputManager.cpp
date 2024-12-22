#include"../include/InputManager.h"

void InputManager::bindKey(KeyboardKey key) {
    // Ensure the key is initialized in the map
    if (keyStates.find(key) == keyStates.end()) {
        keyStates[key] = false; // Default state: not pressed
    }
}

void InputManager::addListener(Listener& listener) {
    if (find(listeners.begin(), listeners.end(), &listener) == listeners.end()) {
        listeners.push_back(&listener);
    }
}

void InputManager::removeListener(Listener& listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), &listener), listeners.end());
}

void InputManager::update() {
    if (keyStates.empty()) return;

    for (auto& [key, state] : keyStates) {
        // Check if key is currently pressed
        bool isPressed = IsKeyPressed(key);

        // If state has changed, notify listeners
        if (isPressed != state) {
            for (auto listener : listeners) {
                if (listener) {
                    listener->onKey(key, isPressed);
                }
            }
            state = isPressed; // Update stored state
        }
    }
}