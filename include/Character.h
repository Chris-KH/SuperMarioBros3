#pragma once
#include "Animation.h"
#include "Sprite.h"
//#include "Hitbox.h"
#include"InputManager.h"
#include"CharacterState.h"

class Character : public Sprite, public InputManager::Listener  {
protected:
    CharacterState* state;
    InputManager* inputManager;
    bool orientation; //True for right, false for left
    bool jumping;
    bool dead; //Character dead or not
    
    int score; // Score
    int coins; // Coin count
    int lives; // Live count
public:
    enum class CHACRACTER {
        MARIO,
        LUIGI
    };

    //Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE) {};
    //virtual ~Character();
    //
    //virtual EntityType getType() const override { return EntityType::CHACRACTER; }

    //virtual CHACRACTER getCharacterType() const = 0;

    //virtual void update(float deltaTime) = 0;
    //    
    //virtual void onKey(KeyboardKey key, bool pressed) = 0;

    //virtual bool isJumping() const { return jumping; };
    //virtual bool isDead() const { return dead; };
};

