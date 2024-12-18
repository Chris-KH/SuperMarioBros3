#pragma once
#include"Global.h"

class Entity;
class Sprite;
class Character;
class Mario;
class Luigi;
class Enemy;

// State Interface: all states will implement this interface
class CharacterState {
    friend class Character;
public:
    virtual void setState(Character* character) = 0;
    virtual void update(Character* character, float deltaTime) = 0;
    virtual STATE getState() const = 0;
};