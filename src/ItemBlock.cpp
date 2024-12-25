#include "../include/ItemBlock.h"
#include "../include/ItemFactory.h"
#include "../include/GameEngine.h"
#include "../include/Sprite.h"
#include "../include/Character.h"
#include "../include/Fireball.h"

ItemBlock::ItemBlock(Vector2 pos, Vector2 size) : BaseBlock(pos, size) {
    sprite = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/tiles1.txt/item_block")->clone();
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
        Item* release = factory.createItem(item, {getX(), getY() - getSize().y / 2.f}, object->getOrientation(), subType);
        release->setAppearBottom(getTop());
        if (item == COIN) globalGameEngine->addScore(100);
        globalGameEngine->addItem(release);
        hasItem = false;
        free(this->currentAnimation);
        this->currentAnimation = nullptr;
        sprite = RESOURCE_MANAGER.getAnimation("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Animation/miscellaneous.txt/empty_block")->clone();
        setAnimation(sprite);
    }
}

void ItemBlock::setItem(ItemType item, int subtype)
{
    hasItem = true;
    this->item = item;
    if (item == COIN) this->subType = BLOCK_COIN;
    else this->subType = subtype;
}
