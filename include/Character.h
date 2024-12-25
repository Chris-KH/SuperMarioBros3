#ifndef CHARACTER_H
#define CHARACTER_H

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
class Shell;
class Star;
class BaseBlock;
class MovingBlock;
class GameEngine;

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

    Animation* deadAniamtion;

    //Animation* lostSuperSuit;
    //Animation* lostFireSuit;

    Phase phase;
    CharacterState* state;
    InputManager& inputManager;
    bool lostLife; //Character dead or not
    bool sitting;
    
    int scores; // Score
    int coins; // Coin count
    int lives; // Live count
    float invicibleStarTime;

    Shell* holdShell;
    bool holding;

    MovingBlock* movingBlockStandOn;
    Vector2 specificVelocity;

    float countThrowTime;
    float countImmortalTime;
    unsigned indexRender;
    vector<bool> renderImmortal;

    bool standingUp;

    const float DEAD_PLAYER_INITIAL_VELOCITY = 120.f; 
    const float DEAD_PLAYER_GRAVITY = 1000.f;      

    const float MAX_WALK_VELOCITY = 100.f;
    const float JET_STOMP_VELOCITY = -200.f;

    const float STAR_INVICIBLE_TIME = 12.f;
    const float TRANSFORM_TIME = 1.f; 

    const float IMMORTAL_TIME = 3.f;
    const float FIREBALL_CHARGE_TIME = 0.f;
public:
    Character(Vector2 pos = { 0, 0 }, Vector2 size = { 0, 0 });
    virtual ~Character();
    
    virtual EntityType getType() const override;

    virtual CharacterType getCharacterType() const = 0;
    virtual void resetInGame();
    virtual void update(float deltaTime) override;
        
    virtual void onKey(KeyboardKey key, bool pressed) override;

    virtual void draw(float deltaTime = GetFrameTime()) override;

    virtual void reset();

    virtual void setPhase(Phase phase);
	virtual const Phase& getPhase() const;

    virtual STATE getState() const;
    bool isInvicible() const;
    bool isSitting() const;

    bool isLostLife() const;
    void setLostLife(bool lostLife);
    bool isIdle() const;
    bool isStadingUp() const;

    int getLives() const;
    void setLives(int lives);

    int getCoins() const;
    void setCoins(int coins);

    int getScores() const;
    void setScores(int score);

    bool isHolding() const;
    void setHoldingShell(Shell* shell);
    Shell* getHoldShell() const;

    void setMovingBlockStandOn(MovingBlock* block);
    MovingBlock* getMovingBlockStandOn() const;

    void setIdleAnimation();
    void setWalkAnimation();
    void setRunAnimation();
    void setJumpAnimation();
    void setStopAnimation();
    void setFallAnimation();
    void setSitAnimation();
    void setFlyAnimation();
    void setHoldAnimation();
    void setStarInvicibleTime(float invicibleStarTime);
    void setSitting(bool sitting);
    void setHolding(bool holding);
	void transform(STATE type);
    void lostSuit();
	void collisionWithItem(const Item* item);
    void collisionWithEnemy(Enemy* enemy, Edge edge = TOP_EDGE);
	void collisionWithFireball(Fireball* fireball);
};
#endif // !CHARACTER_H