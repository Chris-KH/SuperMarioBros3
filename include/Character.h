#pragma once
#include "Animation.h"
#include "Sprite.h"
//#include "Hitbox.h"
#include"Global.h"
#include"CharacterState.h"
#include"NormalState.h"
#include"SuperState.h"
#include"FireState.h"
#include"StarState.h"

class Character : public Sprite, public InputManager::Listener  {
    friend class CharacterState;
    friend class NormalState;
    friend class SuperState;
    friend class FireState;
    friend class StarState;

protected:
    CharacterState* state;
    InputManager& inputManager;
    bool orientation; //True for right, false for left
    bool jumping;
    bool dead; //Character dead or not
    
    int scores; // Score
    int coins; // Coin count
    int lives; // Live count
    float invicible;

    const float DEAD_PLAYER_INITIAL_VELOCITY = 400.f; 
    const float DEAD_PLAYER_GRAVITY = 2000.f;         
    const int INVICIBLE_TIME = 3.f;
public:
    enum class CHACRACTER {
        MARIO,
        LUIGI
    };

    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE): Sprite(pos, size, col)
        , inputManager(INPUT_MANAGER) {
        scores = 0;
        coins = 0;
        lives = 5;
        state = new NormalState();

        reset();
    };
    virtual ~Character() = default;
    
    virtual EntityType getType() const override { return EntityType::CHACRACTER; }

    virtual CHACRACTER getCharacterType() const = 0;

    
    virtual void update(float deltaTime) = 0;
        
    virtual void onKey(KeyboardKey key, bool pressed) = 0;

    virtual void reset() {
        orientation = true;
        jumping = false;
        dead = false;
        invicible = 0;
    }
    virtual CharacterState::STATE getState() const {
        return state->getState();
    }
    virtual bool isJumping() const { return jumping; }
    virtual bool isDead() const { return dead; }
    virtual bool isInvicible() const { return invicible > 1e-9; }
    virtual int getLives() const { return lives; }
    virtual int getCoins() const { return coins; }
    virtual int getScores() const { return scores; }
};



