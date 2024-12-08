#pragma once

class Entity;
class Sprite;
class Character;
class Enemy;

// State Interface: all states will implement this interface
class CharacterState {
public:
    enum STATE {
        NORMAL,
        SUPER,
        FIRE,
        INVINCIBLE
    };
    virtual ~CharacterState() = 0;
    
    virtual void update(const Character* character) = 0;
};