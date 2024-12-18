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
    Animation* flyLeft;
    Animation* sitLeft;

    Animation* idleRight;
    Animation* walkRight;
    Animation* runRight;
    Animation* stopRight;
    Animation* jumpRight;
    Animation* fallRight;
    Animation* flyRight;
    Animation* sitRight;

    CharacterState* state;
    InputManager& inputManager;
    bool orientation; //True for right, false for left
    bool dead; //Character dead or not
    bool sitting;
    
    int scores; // Score
    int coins; // Coin count
    int lives; // Live count
    float invicible;

    const float DEAD_PLAYER_INITIAL_VELOCITY = 300.f; 
    const float DEAD_PLAYER_GRAVITY = 1000.f;      

    const float MAX_WALK_VELOCITY = 100.f;

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

    
    virtual void update(float deltaTime) {};
        
    virtual void onKey(KeyboardKey key, bool pressed) = 0;

    virtual void draw(float deltaTime = GetFrameTime());

    virtual void setState();
    virtual void reset();
    
    void setAnimation(Animation* animation);

    virtual CharacterState::STATE getState() const;
    bool isDead() const;
    bool isInvicible() const;
    bool isSitting() const {
        return sitting;
    }
    bool isIdle() const;
    int getLives() const;
    int getCoins() const;
    int getScores() const;

    void setIdleAnimation() {
        if (orientation) setAnimation(idleRight);
        else setAnimation(idleLeft);
    }

    void setWalkAnimation() {
        if (orientation) setAnimation(walkRight);
        else setAnimation(walkLeft);
    }

    void setRunAnimation() {
        if (orientation) setAnimation(runRight);
        else setAnimation(runLeft);
    }

    void setJumpAnimation() {
        if (orientation) setAnimation(jumpRight);
        else setAnimation(jumpLeft);
    }

    void setStopAnimation() {
        if (orientation) setAnimation(stopRight);
        else setAnimation(stopLeft);
    }

    void setFallAnimation() {
        if (orientation) setAnimation(fallRight);
        else setAnimation(fallLeft);
    }

    void setSitAnimation() {
        if (orientation) setAnimation(sitRight);
        else setAnimation(sitLeft);
    }

    void setFlyAnimation() {
        if (orientation) setAnimation(flyRight);
        else setAnimation(flyLeft);
    }

    void setInvicible(bool invicible) {
        this->invicible = invicible;
    }

    void setSitting(bool sitting) {
        this->sitting = sitting;
    }
};



