#pragma once

#include "raylib.h"
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>

//I move all enum type to Global.h

class BaseBlock : public Entity {
public:
	BaseBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = ORANGE) : Entity(pos,size,color), sprite(nullptr) {}
	virtual ~BaseBlock(){};
	void setSprite(const Animation* blockAnimation)
	{
		sprite = blockAnimation;
	}
	EntityType getType() const {
		return BLOCK;
	}
	virtual BlockType getBlockType()const = 0;
	virtual void draw(float deltaTime = GetFrameTime()) // may be deleted in future
	{
		Rectangle destRect = { getPosition().x, getPosition().y, getSize().x, getSize().y };
		Rectangle srcRect = { 0, 0, getSize().x, getSize().y };
		DrawRectangleRec(destRect, getColor()); // Replace with texture drawing
		//current Animation rendering
	}
	virtual void update(float deltaTime) override {} // moving,.... implement in derived classes
protected:
	const Animation* sprite = nullptr;
};
class Floor : public BaseBlock
{
private:
public:
	Floor(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = GREEN) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return FLOOR; }
	void update(float deltaTime)
	{
		//static floor ko có tác động làm thay đổi
	}
};
class Brick : public BaseBlock
{
private:
	bool isBroken = false;
public:
	Brick(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BROWN) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return BRICK; }
	void update(float deltaTime) override
	{
		if (isBroken) {
			setColor(BLANK);
			setSize({0, 0});
		}
	}
	void breakBrick() {
		isBroken = true;
	}

};
class SolidBlock : public BaseBlock
{
private:
public:
	SolidBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = DARKBROWN) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return SOLIDBLOCK; }
	void update(float deltaTime) 
	{
		//solid brock bình thường cũng ko tác động làm thay đổi
	}
};

class MovingBlock : public BaseBlock
{
private:
	Vector2 velocity = { 50.0f, 50.0f }; // Movement speed
	float boundLeft, boundRight;       // Horizontal bounds
	float boundTop, boundBottom;       // Vertical bounds

public:
	MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 16, 16 }, Color color = DARKGRAY)
		: BaseBlock(pos, size, color),
		boundLeft(pos.x), boundRight(pos.x),
		boundTop(pos.y), boundBottom(pos.y) {}

	BlockType getBlockType() const override { return MOVINGBLOCK; }

	void setBounds(float left, float right, float top, float bottom)
	{
		Vector2 pos = getPosition(); // Get the current position of the block

		// If any bound is invalid, default to the current position
		if (left >= right || top >= bottom)
		{
			TraceLog(LOG_WARNING, "Invalid bounds! Defaulting to block's current position.");
			boundLeft = pos.x;
			boundRight = pos.x;
			boundTop = pos.y;
			boundBottom = pos.y;
		}
		else
		{
			boundLeft = left;
			boundRight = right;
			boundTop = top;
			boundBottom = bottom;
		}
	}

	Vector2 getVelocity() const { return velocity; }
	void setVelocity(Vector2 newVelocity) { velocity = newVelocity; }

	void update(float deltaTime)
	{
		Vector2 pos = getPosition();

		pos.x += velocity.x * deltaTime;
		pos.y += velocity.y * deltaTime;

		if (pos.x <= boundLeft || pos.x + getSize().x >= boundRight)
		{
			velocity.x = -velocity.x;
		}

		// Vertical bounds check
		if (pos.y <= boundTop || pos.y + getSize().y >= boundBottom)
		{
			velocity.y = -velocity.y;
		}

		setPosition(pos);
	}
};


class ItemBlock : public BaseBlock
{
private:
	bool hasItem = true;
public:
	ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = YELLOW) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return ITEMBLOCK; }
	void update(float deltaTime)
	{
		if (hasItem) {
			//xử lý Item
			hasItem = false;
		}

	}
};

class HiddenBlock : public BaseBlock
{
private:
	bool revealed = false;
public:
	HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = WHITE) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return HIDDEN; }
	void update(float deltaTime) override
	{
		if (revealed) {
			setColor(ORANGE);
		}
	}
	void reveal() {
		revealed = true;
	}

};

class SpikeBlock : public BaseBlock
{
private:
public:
	SpikeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLACK) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return SPIKE; }
	void update(float deltaTime)
	{
		//Check collision với Mario
		//Nếu Mario có va chạm, check trạng thái
		//Nếu ko phải trạng thái bất tử, game over
	}
};

class PipeBlock : public BaseBlock
{
private:
public:
	PipeBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = DARKGREEN) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return PIPE; }
	void update(float deltaTime)
	{
		//Check collision với Mario
		//Nếu Mario chạm đến, kết màn và chuyển sang màn chơi mới
	}
};

class DecorBlock : public BaseBlock
{
private:
public:
	DecorBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK) : BaseBlock(pos, size, color) {}
	BlockType getBlockType() const override { return DECOR; }
	void update(float deltaTime)
	{
		//something
	}
};

class TemporaryBlock : public BaseBlock
{
private:
	float lifeTime;
	bool isDying;
	bool dead;
public:
	TemporaryBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = BLANK) : BaseBlock(pos, size, color)
	{
		isDying = false;
		dead = false;
		lifeTime = 1.5;
	}
	BlockType getBlockType() const override { return TEMPBLOCK; };
	void update()
	{
		if (!dead)
		if (isDying)
		{
			float deltaTime = GetFrameTime();
			lifeTime -= deltaTime;
			if (lifeTime <= 0)
			{
				dead = true;

			}
		}
	}

};


/*Entity* BaseBlock::spikeMario() {
	for (Entity* entity : entity managing = quản lý trong entity) {Có va chạm trả về entity}
	Ko va chạm trả về nullptr
}*/

/*void setGameOver(bool isGameOver) {
    GameStateManager::setGameOverFlag(isGameOver); //set game over
}*/

/*void advanceToNextLevel() {
    LevelManager::loadNextLevel(GameEngine); // Load level tiếp theo <- Lấy từ GameEngine
}*/

