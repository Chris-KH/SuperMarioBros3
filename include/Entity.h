#pragma once
#include"Collision.h"
#include <raylib.h>

class Entity {
private:
	Vector2 position;
	Vector2 size;
	Texture2D texture;
	Rectangle sourceRect;
	Vector2 velocity;
	float speed;
	bool isFlipped;
	ICollisionStrategy* collisionStrategy;//
public:
	// Constructor
	Entity(Vector2 pos, Vector2 sz, Texture2D tex, float spd) 
		: position(pos), size(sz), texture(tex), velocity{ 0, 0 }, collisionStrategy(nullptr), speed(spd), isFlipped(false) 
	{
		sourceRect = { 0, 0, (float)tex.width, (float)tex.height };
	}

	Rectangle getHitBox();
	void setPosition(Vector2 newPos);
	void handleInput();
	void move();
	void draw() ;
	void unloadTexture() const;
	void setCollisionStrategy(ICollisionStrategy* strategy); //
	bool checkCollision(const Block& block);//

};


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



