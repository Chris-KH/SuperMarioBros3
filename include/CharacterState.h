#pragma once

class Entity;
class Sprite;
class Character;
class Enemy;

// State Interface: all states will implement this interface
class CharacterState {
    friend class Character;
public:
    enum STATE {
        NORMAL,
        SUPER,
        FIRE,
        STAR
    };
    virtual ~CharacterState() = 0;

    virtual void update(const Character* character, float deltaTime) = 0;
    virtual STATE getState() const = 0;
};