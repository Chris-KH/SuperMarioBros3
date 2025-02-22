#pragma once
#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"

class GameEngine;

class Entity {
private:
    Vector2 position; // Position of the entity
    Vector2 size;     // Size of the entity
    bool dead;           // Indicates if the sprite is "dead"
protected:
    Animation* currentAnimation; 
    float playTime;
public:
    Entity(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    Entity(const Entity& other);

    virtual ~Entity();
        
    // Getters
    virtual float getX() const;
    virtual float getY() const;
    virtual float getWidth() const;
    virtual float getHeight() const;
    virtual Rectangle getRectangle() const;
    virtual const Vector2& getSize() const ;
    virtual const Vector2& getPosition() const;
    virtual EntityType getType() const = 0;
    virtual float getCenterX() const;
    virtual float getCenterY() const;
    virtual float getBottom() const;
    virtual float getLeft() const;
    virtual float getRight() const;
    virtual float getTop() const;
    virtual Vector2 getCenter() const;

    // Setters
    virtual void setPosition(Vector2 pos);
    virtual void setXPosition(float x);
    virtual void setYPosition(float y);
    virtual void setSize(Vector2 sz);
    virtual void setCenter(Vector2 center);
    
    // Pure virtual draw function
    virtual void draw(float deltaTime = GetFrameTime()) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void setAnimation(Animation* animation, float time = 0.f);
    virtual void setAnimation(const string& name, float time = 0.f);
    virtual void updateTime(float deltaTime = GetFrameTime());

    virtual void killEntity();
	virtual bool isDead() const;
};
