#pragma once
#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"

class Entity {
private:
    Vector2 position; // Position of the entity
    Vector2 size;     // Size of the entity
    Color color;      // RGBA color of the entity
protected:
    Animation* currentAnimation; 

public:
    Entity(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = WHITE);
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
    virtual float getCenterX() const;
    virtual float getCenterY() const;
    virtual float getBottom() const;
    virtual float getLeft() const;
    virtual float getRight() const;
    virtual float getTop() const;

    // Setters
    virtual void setPosition(Vector2 pos);
    virtual void setXPosition(float x);
    virtual void setYPosition(float y);
    virtual void setSize(Vector2 sz);
    virtual void setColor(Color col);
    
    // Pure virtual draw function
    virtual void draw(float deltaTime = GetFrameTime()) const = 0;
    virtual void update(float deltaTime) = 0;
    virtual void setAnimation(Animation* animation);
    virtual void setAnimation(const string& name);
     
};
