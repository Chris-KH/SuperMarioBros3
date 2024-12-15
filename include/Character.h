#pragma once
#include "Animation.h"
#include "Sprite.h"
//#include "Hitbox.h"
#include"Global.h"
#include"CharacterState.h"

class CharacterState;
class NormalState;
class SuperState;
class FireState;
class StarState;

class Character : public Sprite, public InputManager::Listener  {
    friend class CharacterState;
    friend class NormalState;
    friend class SuperState;
    friend class FireState;
    friend class StarState;

protected:
    Animation* idleLeft;
    Animation* walkLeft;
    Animation* runLeft;
    Animation* stopLeft;
    Animation* jumpLeft;
    Animation* fallLeft;

    Animation* idleRight;
    Animation* walkRight;
    Animation* runRight;
    Animation* stopRight;
    Animation* jumpRight;
    Animation* fallRight;

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
    const float INVICIBLE_TIME = 1.f;
    const float TRANSFORM_TIME = 1.f; 
public:
    enum class CHACRACTER {
        MARIO,
        LUIGI
    };

    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE);
    virtual ~Character();
    
    virtual EntityType getType() const override;

    virtual CHACRACTER getCharacterType() const = 0;

    
    virtual void update(float deltaTime) = 0;
        
    virtual void onKey(KeyboardKey key, bool pressed) = 0;

    void draw();

    virtual void setState();
    virtual void reset();
    void setJumping(bool value);
    
    void setAnimation(Animation* animation);

    virtual CharacterState::STATE getState() const;
    virtual bool isJumping() const;
    virtual bool isDead() const;
    virtual bool isInvicible() const;
    virtual bool isIdle() const;
    virtual int getLives() const;
    virtual int getCoins() const;
    virtual int getScores() const;
};



