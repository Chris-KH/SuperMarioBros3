#pragma once
#include"../lib/bits/stdc++.h"
#include "raylib.h"
#include <raylib.h>

using namespace std;

class InputManager {
public:
    //An interface for listeners to input events.
    class Listener
    {
    public:
        virtual ~Listener() {}

        //Event fired when a key state changes.
        virtual void onKey(KeyboardKey key, bool pressed) = 0;
    };

    InputManager() = default;
    ~InputManager() = default;

    // Bind a key to listen for state changes
    void bindKey(KeyboardKey key);

    // Add a listener for key events
    void addListener(Listener& listener);

    // Remove a listener
    void removeListener(Listener& listener);

    // Update input state (should be called every frame)
    void update();

private:
    unordered_map<KeyboardKey, bool> keyStates; // Map of key states (pressed or not)
    vector<Listener*> listeners;       // List of listeners
};

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
        bool isPressed = IsKeyDown(key);

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