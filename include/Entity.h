<<<<<<< HEAD
﻿//#pragma once

#include "Collision.h"
#include "../lib/raylib.h"
=======
#pragma once
#include <raylib.h>
#include "Animation.h"
#include "State.h"
>>>>>>> 091e26b87b428f4aa13e201d3101b6b79ccfac81

class Entity {
protected:
    Vector2 position; // Position of the entity
    Vector2 size;     // Size of the entity
    Color color;      // RGBA color of the entity

    Animation* currentAnimation; 
    State* currentState;
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

    // Setters
    virtual void setPosition(Vector2 pos);
    virtual void setSize(Vector2 sz);
    virtual void setColor(Color col);
   
    // Pure virtual draw function
    virtual void draw() const = 0;

    // Collision detection 
};

<<<<<<< HEAD

//
//class Entity {
//public:
//    Rectangle hitbox;
//    ICollisionStrategy* collisionStrategy;
//    float speed;  // Movement speed
//
//    Entity(float x, float y, float width, float height, float speed = 200.0f)
//        : hitbox{ x, y, width, height }, collisionStrategy(nullptr), speed(speed) {}
//
//    void setCollisionStrategy(ICollisionStrategy* strategy) {
//        collisionStrategy = strategy;
//    }
//
//    bool checkCollision(const Block& block) {
//        if (collisionStrategy)
//            return collisionStrategy->collides(*this, block);
//        return false;
//    }
//};


=======
>>>>>>> 091e26b87b428f4aa13e201d3101b6b79ccfac81
