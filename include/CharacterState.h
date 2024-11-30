#pragma once

class Entity;
class Sprite;
class Character;
class Enemy;

// State Interface: all states will implement this interface
class CharacterState {
public:
    virtual ~CharacterState() = default;
    

};