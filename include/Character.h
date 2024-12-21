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
public:
    enum Phase {
        DEFAULT_PHASE,
        TRANSFORM_PHASE,
        DEAD_PHASE,
        EXIT_PHASE,
        ENTER_PHASE
    };

protected:
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
	
    STATE lastState;
    Phase phase;
    CharacterState* state;
    InputManager& inputManager;
    bool lostLife; //Character dead or not
    bool sitting;
    
    int scores; // Score
    int coins; // Coin count
    int lives; // Live count
    float invicibleTime;

    const float DEAD_PLAYER_INITIAL_VELOCITY = 300.f; 
    const float DEAD_PLAYER_GRAVITY = 1000.f;      

    const float MAX_WALK_VELOCITY = 100.f;
    const float JET_STOMP_VELOCITY = -200.f;

    const float INVICIBLE_TIME = 12.f;
    const float TRANSFORM_TIME = 1.f; 
public:
    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 }, Color col = WHITE);
    virtual ~Character();
    
    virtual EntityType getType() const override;

    virtual CharacterType getCharacterType() const = 0;

    virtual void update(float deltaTime) override {};
        
    virtual void onKey(KeyboardKey key, bool pressed) = 0;

    virtual void draw(float deltaTime = GetFrameTime()) override;

    virtual void reset();

    virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;

    virtual STATE getState() const;
    bool isInvicible() const;
    bool isSitting() const {
        return sitting;
    }

    bool isLostLife() const {
        return this->lostLife;
    }
    void setLostLife(bool lostLife) {
        this->lostLife = lostLife;
    }
    bool isIdle() const;
    int getLives() const;
    void setLives(int lives);
    int getCoins() const;
    void setCoins(int coins);
    int getScores() const;
    void setScores(int score);

    void setIdleAnimation();
    void setWalkAnimation();
    void setRunAnimation();
    void setJumpAnimation();
    void setStopAnimation();
    void setFallAnimation();
    void setSitAnimation();
    void setFlyAnimation();
    void setInvicible(float invicibleTime);
    void setSitting(bool sitting);

	void transform(STATE type);
	void collisionWithItem(const Item* item);

    void collisionWithEnemy(Enemy* enemy, Edge edge = TOP_EDGE);
    
	//void collisionWithFireball(const Fireball* fireball);
};



