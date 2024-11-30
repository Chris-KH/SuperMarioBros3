#pragma once
#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"

enum EntityType {
    CHACRACTER,
    ENEMY,
    ITEM
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

    Animation* currentAnimation; 
    Animation* nextAnimation;
public:
    Entity(Vector2 pos = { 0, 0 }, Vector2 sz = { 1, 1 }, Color col = Color(255, 255, 255, 255));
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

    // Collision detection 
    //virtual void checkCollision(const Entity& other);
     
};

