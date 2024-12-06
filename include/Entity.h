#pragma once
#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"
#include "ResourceManager.h"

enum EntityType {
    CHACRACTER,
    ENEMY,
    ITEM,
    BLOCK


};

//enum class CHACRACTER {
//    Mario,
//    Luigi
//};
//
//enum class ITEM {
//    Coin,
//    Mushroom
//};
//
//enum class ENEMY {
//    Beetle,
//    Bowser,
//    Goomba,
//    Plant,
//    Spiny,
//    Thwomp,
//    Lakitu,
//    KoopaTroopa
//};

class Entity {
private:
    Vector2 position; // Position of the entity
    Vector2 size;     // Size of the entity
    Color color;      // RGBA color of the entity
protected:
    Animation* currentAnimation; 
    Animation* nextAnimation;

    const ResourceManager* resourceManager;
public:
    Entity(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK);
    Entity(const Entity& other);

    virtual ~Entity() {}
        
    // Getters
    virtual float getX() const;
    virtual float getY() const;
    virtual float getWidth() const;
    virtual float getHeight() const;
    virtual Rectangle getRectangle() const;
    virtual Vector2 getSize() const ;
    virtual Vector2 getPosition() const;
    virtual Color getColor() const;
    virtual EntityType getType() const = 0;


    // Setters
    virtual void setPosition(Vector2 pos);
    virtual void setSize(Vector2 sz);
    virtual void setColor(Color col);
    
    // Pure virtual draw function
    virtual void draw() const = 0;
    virtual void update(float deltaTime) = 0;
    //virtual void setAnimation(Animation* animation);

    //Collision detection 
    //virtual void checkCollision(const Entity& other);
     
};
