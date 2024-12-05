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