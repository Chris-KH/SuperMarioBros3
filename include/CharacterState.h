#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H
#include"Global.h"

class Entity;
class Sprite;
class Character;
class Mario;
class Luigi;
class Enemy;

// State: all states will implement this interface
class CharacterState {
private:
	Character* character;
public:
	CharacterState(Character* character = nullptr);
	virtual ~CharacterState() = default;
    virtual void setAnimation() = 0;
    virtual void update(float deltaTime) = 0;
    virtual STATE getState() const = 0;

	virtual void setCharacter(Character* character = nullptr);

	virtual Character* getCharacter() const;
};
#endif