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
class StarmanState;
class SuperStarmanState;
class FireStarmanState;
class Item;
class Enemy;
class Fireball;

//Base class for all character
class Character : public Sprite, public InputManager::Listener  {
    friend class CharacterState;
    friend class NormalState;
    friend class SuperState;
    friend class FireState;
    friend class StarmanState;
	friend class SuperStarmanState;
	friend class FireStarmanState;

protected:
    enum Phase {
		DEFAULT_PHASE,
		TRANSFORM_PHASE,
		DEAD_PHASE,
		EXIT_PHASE,
		ENTER_PHASE
    };

    Animation* idleLeft;
    Animation* walkLeft;
    Animation* runLeft;
    Animation* stopLeft;
    Animation* jumpLeft;
    Animation* fallLeft;
    Animation* flyLeft;
    Animation* sitLeft;
    Animation* holdLeft;
	Animation* throwLeft;
	Animation* kickLeft;

    Animation* idleRight;
    Animation* walkRight;
    Animation* runRight;
    Animation* stopRight;
    Animation* jumpRight;
    Animation* fallRight;
    Animation* flyRight;
    Animation* sitRight;
	Animation* holdRight;
	Animation* throwRight; 
	Animation* kickRight;

    //Animation* lostSuperSuit;
    //Animation* lostFireSuit;
	
    Phase phase;
    CharacterState* state;
    InputManager& inputManager;
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
    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE);
    virtual ~Character();
    
    virtual EntityType getType() const override;

    virtual CharacterType getCharacterType() const = 0;

    
    virtual void update(float deltaTime) {};
        
    virtual void onKey(KeyboardKey key, bool pressed) = 0;

    virtual void draw(float deltaTime = GetFrameTime());

    virtual void setState();
    virtual void reset();

    virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;

    virtual STATE getState() const;
    bool isDead() const;
    bool isInvicible() const;
    bool isSitting() const {
        return sitting;
    }
    bool isIdle() const;
    int getLives() const;
    int getCoins() const;
    int getScores() const;

    void setIdleAnimation();
    void setWalkAnimation();
    void setRunAnimation();
    void setJumpAnimation();
    void setStopAnimation();
    void setFallAnimation();
    void setSitAnimation();
    void setFlyAnimation();
    void setInvicible(bool invicible);
    void setSitting(bool sitting);

 //   void collisionWithEnemy();
	//void collisionWithItem(const Item* item);
	//void collisionWithFireball(const Fireball* fireball);
};



