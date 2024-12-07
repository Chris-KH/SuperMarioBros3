#pragma once

#include "raylib.h"
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <string>

enum BlockType {
    FLOOR,
    BRICK, // breakable
    SOLIDBLOCK, // unmovable, unbreakable
    MOVINGBLOCK,
    ITEMBLOCK,
    HIDDEN,
    SPIKE,
    PIPE,
	TEMPBLOCK,
    DECOR
};

class BaseBlock : public Entity
{
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
	virtual void draw() const// may be deleted in future
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
	Vector2 velocity = { 50.0f, 50.0f }; // diagonal velocity
	float leftAlign, rightAlign;       // horizontal bounds
	float topAlign, bottomAlign;       // vertical bounds

public:
	MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = DARKGRAY)
		: BaseBlock(pos, size, color)
	{
		velocity = { 50, 50 };
		leftAlign = 0;
		topAlign = 0;
		rightAlign = 0;
		bottomAlign = 0;
	}

	BlockType getBlockType() const override { return MOVINGBLOCK; }

	void setHorizontalBounds(float left, float right)
	{
		leftAlign = left;
		rightAlign = right;
	}

	void setVerticalBounds(float top, float bottom)
	{
		topAlign = top;
		bottomAlign = bottom;
	}
	Vector2 getVelocity()
	{
		return velocity;
	}
	void setVelocity(Vector2 newVelocity)
	{
		velocity = newVelocity;
	}

	void update(float deltaTime)
	{
		Vector2 pos = getPosition();

		// Update position based on velocity
		pos.x += velocity.x * deltaTime;
		pos.y += velocity.y * deltaTime;

		// Handle horizontal bouncing
		if (pos.x < leftAlign) // Left boundary
		{
			pos.x = leftAlign; // Clamp position
			if (velocity.x < 0) // Reverse only if moving left
				velocity.x = std::abs(velocity.x); // Move right
		}
		else if (pos.x + getSize().x > rightAlign) // Right boundary
		{
			pos.x = rightAlign - getSize().x; // Clamp position
			if (velocity.x > 0) // Reverse only if moving right
				velocity.x = -std::abs(velocity.x); // Move left
		}

		// Handle vertical bouncing
		if (pos.y < topAlign) // Top boundary
		{
			pos.y = topAlign; // Clamp position
			if (velocity.y < 0) // Reverse only if moving up
				velocity.y = std::abs(velocity.y); // Move down
		}
		else if (pos.y + getSize().y > bottomAlign) // Bottom boundary
		{
			pos.y = bottomAlign - getSize().y; // Clamp position
			if (velocity.y > 0) // Reverse only if moving down
				velocity.y = -std::abs(velocity.y); // Move up
		}

		// Update the position after corrections
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
	BlockType getBlockType() { return PIPE; }
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


//
//class Block {
//public:
//	Block(float x, float y, float width, float height, BlockType type, const std::string& texturePath = "") : hitbox{ x, y, width, height }, velocity{0.0f, 0.0f}, type(type), isSolid(true), itemCounting(0) {
//        if (!texturePath.empty()) {
//            texture = LoadTexture(texturePath.c_str());
//            loadTexture = true;
//        } else {
//            loadTexture = false;
//        }
//    }
//
//    ~Block() {
//        if (loadTexture) {
//            UnloadTexture(texture);
//        }
//    }
//
//	Rectangle getHitbox() const {
//        switch (type) {
//            case breakable:
//            return { hitbox.x, hitbox.y, hitbox.width, 0 };
//            default:
//            return hitbox;
//        }
//    }
//
//    void handleMoving(float deltaTime) {
//        if (type == moving) {
//            hitbox.x += velocity.x * deltaTime;
//            hitbox.y += velocity.y * deltaTime;
//        }
//    }
//
//    void hit() {
//        if (!isSolid) return;
//        switch (type) {
//            case breakable:
//            isSolid = false;
//            break;
//
//            case itemRelease:
//            //Phải có Item trước
//            break;
//
//            case hidden:
//            type = normal;
//            isSolid = true;
//            break;
//
//        }
//    }
//
//    void savetoBinaryFile(std::ofstream &file) const {
//        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
//        file.write(reinterpret_cast<const char*>(&hitbox), sizeof(hitbox));
//        file.write(reinterpret_cast<const char*>(&isSolid), sizeof(isSolid));
//        file.write(reinterpret_cast<const char*>(&itemCounting), sizeof(itemCounting));
//    }
//
//    void loadfromBinaryFile(std::ifstream &file) {
//        file.read(reinterpret_cast<char*>(&type), sizeof(type));
//        file.read(reinterpret_cast<char*>(&hitbox), sizeof(hitbox));
//        file.read(reinterpret_cast<char*>(&isSolid), sizeof(isSolid));
//        file.read(reinterpret_cast<char*>(&itemCounting), sizeof(itemCounting));
//    }
//
//    virtual void render() const {
//        if (loadTexture) {
//            DrawTexture(texture, static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), WHITE);
//        } else {
//            Color color = GetColor(type);
//            DrawRectangle(static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), static_cast<int>(hitbox.width), static_cast<int>(hitbox.height), color);
//        }
//    }
//
//private:
//	Rectangle hitbox;
//    Vector2 velocity;
//    BlockType type;
//    bool isSolid;
//    int itemCounting;
//    Texture2D texture;
//    bool loadTexture;
//
//    static constexpr float bouncingHeight = 10.0f;
//    static constexpr float bounceDuration = 0.1f;
//
//    void releaseItem() {
//        if (itemCounting > 0) {
//            
//            itemCounting--;
//        }
//        if (itemCounting == 0) {
//            type = normal;
//        }
//    }
//
//    Color GetColor(BlockType type) const {
//        switch (type) {
//            case normal: return GRAY;
//            case breakable: return RED;
//            case moving: return BROWN;
//            case itemRelease: return YELLOW;
//            case hidden: return Fade(GRAY, 1.0f);
//            case lava: return ORANGE;
//            case pipe: return GREEN;
//        }
//    }    
//};