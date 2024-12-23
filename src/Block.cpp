/*#include "../include/Block.h"
#include "../include/Global.h"
#include "../include/ItemFactory.h"
#include "../include/GameEngine.h"
BaseBlock::BaseBlock(Vector2 pos, Vector2 size, Color color) : Entity(pos, size, color), sprite(nullptr) {}

BaseBlock::~BaseBlock() {
    if (sprite)
        delete sprite;
}

EntityType BaseBlock::getType() const {
    return BLOCK;
}

void BaseBlock::draw(float deltaTime) {
    // Placeholder for drawing logic
}

void BaseBlock::update(float deltaTime) {
    // Placeholder for update logic
}

Floor::Floor(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType Floor::getBlockType() const {
    return FLOOR;
}

void Floor::update(float deltaTime) {
    // Static floor has no dynamic behavior
}

Brick::Brick(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {
    sprite = RESOURCE_MANAGER.getAnimation("gold_brick_block")->clone();
    setAnimation(sprite);
}

void Brick::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

BlockType Brick::getBlockType() const {
    return BRICK;
}

void Brick::update(float deltaTime) {
    currentAnimation->update(deltaTime);
}

void Brick::breakBrick() {
    isBroken = true;
}

SolidBlock::SolidBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType SolidBlock::getBlockType() const {
    return SOLIDBLOCK;
}

void SolidBlock::update(float deltaTime) {
    // No behavior for solid blocks
}

MovingBlock::MovingBlock(Vector2 pos, Vector2 size, Color color)
    : BaseBlock(pos, size, color), boundLeft(pos.x), boundRight(pos.x), boundTop(pos.y), boundBottom(pos.y) {
    sprite = RESOURCE_MANAGER.getAnimation("moving_platform_block")->clone();
    setAnimation(sprite);
}

BlockType MovingBlock::getBlockType() const {
    return MOVINGBLOCK;
}

void MovingBlock::draw(float deltaTime) {
    Vector2 pos = getPosition();
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
    setPosition(pos);
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

void MovingBlock::setBounds(float left, float right, float top, float bottom) {
    Vector2 pos = getPosition();
    if (left >= right || top >= bottom) {
        TraceLog(LOG_WARNING, "Invalid bounds! Defaulting to block's current position.");
        boundLeft = pos.x;
        boundRight = pos.x;
        boundTop = pos.y;
        boundBottom = pos.y;
    }
    else {
        boundLeft = left;
        boundRight = right;
        boundTop = top;
        boundBottom = bottom;
    }
}

Vector2 MovingBlock::getVelocity() const {
    return velocity;
}

void MovingBlock::setVelocity(Vector2 newVelocity) {
    velocity = newVelocity;
}

void MovingBlock::update(float deltaTime) {
    Vector2 pos = getPosition();


    if (pos.x <= boundLeft || pos.x + getSize().x >= boundRight) {
        velocity.x = -velocity.x;
    }

    if (pos.y <= boundTop || pos.y + getSize().y >= boundBottom) {
        velocity.y = -velocity.y;
    }

    currentAnimation->update(deltaTime);
}

ItemBlock::ItemBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {
    sprite = RESOURCE_MANAGER.getAnimation("item_block")->clone();
    item = COIN;
    subType = BLOCK_COIN;
    setAnimation(sprite);
    OgY = pos.y;
}

BlockType ItemBlock::getBlockType() const {
    return ITEMBLOCK;
}

void ItemBlock::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

void ItemBlock::update(float deltaTime) {
    if (isBouncing)
    {
        bounceTime += deltaTime;

        float offset = bounceHeight * sin((bounceTime / bounceDuration) * PI);
        setPosition({ getX(), OgY - offset });

        if (bounceTime >= bounceDuration)
        {
            isBouncing = false;
            setPosition({ getX(), OgY });
        }
    }
    currentAnimation->update(deltaTime);
}

void ItemBlock::releaseItem(const Sprite* object)
{
    if (hasItem)
    {
        isBouncing = true;
        bounceTime = 0.0f; // Reset bounce timer
        ItemFactory& factory = ItemFactory::getInstance();
        Item* release = factory.createItem(item, { getX(), getY() - 29.f }, RIGHT, subType);
        if (item == COIN)
            globalGameEngine->addScore(100);
        globalGameEngine->addItem(release);
        hasItem = false;
        free(this->currentAnimation);
        sprite = RESOURCE_MANAGER.getAnimation("empty_block")->clone();
        setAnimation(sprite);
    }
}

void ItemBlock::setItem(ItemType item, int subtype)
{
    hasItem = true;
    this->item= item;
    if (item == COIN)
        this->subType = BLOCK_COIN;
    else
        this->subType = subtype;
}

HiddenBlock::HiddenBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType HiddenBlock::getBlockType() const {
    return HIDDEN;
}

void HiddenBlock::update(float deltaTime) {
    if (revealed) {
        setColor(ORANGE);
    }
}

void HiddenBlock::reveal()
{

}

SpikeBlock::SpikeBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType SpikeBlock::getBlockType() const {
    return SPIKE;
}

void SpikeBlock::update(float deltaTime) {
    // Placeholder for spike block behavior
}

PipeBlock::PipeBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {}

BlockType PipeBlock::getBlockType() const {
    return PIPE;
}

void PipeBlock::update(float deltaTime) {
    // Placeholder for pipe block behavior
}

DecorBlock::DecorBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color) {
    sprite = RESOURCE_MANAGER.getAnimation("pipe_block_head")->clone();
    setAnimation(sprite);
}

void DecorBlock::draw(float deltaTime) {
    if (currentAnimation == nullptr) return;
    currentAnimation->render(this->getPosition());
}

BlockType DecorBlock::getBlockType() const {
    return DECOR;
}

void DecorBlock::update(float deltaTime) {
    // Placeholder for decor block behavior
}

TemporaryBlock::TemporaryBlock(Vector2 pos, Vector2 size, Color color) : BaseBlock(pos, size, color), lifeTime(1.5), isDying(false), dead(false) {}

BlockType TemporaryBlock::getBlockType() const {
    return TEMPBLOCK;
}

void TemporaryBlock::update() {
    if (!dead && isDying) {
        float deltaTime = GetFrameTime();
        lifeTime -= deltaTime;
        if (lifeTime <= 0) {
            dead = true;
        }
    }
}*/