#pragma once

class Entity;
class Sprite;
class Character;
class Enemy;

// State Interface: all states will implement this interface
class State {
public:
    virtual ~State() = default;
    

};