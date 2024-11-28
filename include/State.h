#pragma once

class Entity;
class Sprite;
class Character;
class Enemy;

// State Interface: all states will implement this interface
class State {
public:
    virtual ~State() = default;

    // Update method: Will be called to update the state logic
    virtual void update(Character* character, float deltaTime) = 0;
    virtual void update(Enemy* enemy, float deltaTime) = 0;

    // Render method: Will be called to render the state-specific behavior
    virtual void render(Character* character) = 0;
    virtual void render(Enemy* enemy) = 0;
};