#pragma once
#include"C:/Users/Dell/Downloads/CS202-SuperMario/lib/raylib.h"
#include<vector>
#include<unordered_map>

using namespace std;

template <class T>
class Singleton;

class InputManager {
    template <class T>
    friend class Singleton;
public:
    //An interface for listeners to input events.
    class Listener
    {
    public:
        virtual ~Listener() {}

        //Event fired when a key state changes.
        virtual void onKey(KeyboardKey key, bool pressed) = 0;
    };

    
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
    InputManager() = default;
    InputManager(const InputManager& other) = delete;
    InputManager& operator=(const InputManager& other) = delete;

    unordered_map<KeyboardKey, bool> keyStates; // Map of key states (pressed or not)
    vector<Listener*> listeners;       // List of listeners
};
