#pragma once
#include"Entity.h"
#include"Block.h"
#include"Character.h"
#include"Enemy.h"
//
//class ICollisionStrategy {
//public:
//    virtual bool collides(Entity& entity, const Block& block) = 0;
//    virtual ~ICollisionStrategy() = default;
//};
//class EntityToBlockPushbackCollision : public ICollisionStrategy {
//public:
//    bool collides(Entity& entity, const Block& block) override;
//};
//class EntityToBLockCollision : public ICollisionStrategy
//{
//public:
//    bool collides(Entity& entity, const Block& block) override;
//};

class CollisionStrategy {
public:
    virtual void resolve(Entity& entityA, Entity& entityB) = 0; // General case
    virtual void resolve(Entity& entity, const Block& block) = 0; // Block-specific case
    virtual ~CollisionStrategy() = default;
};


class EntityBlockCollisionHandler : public CollisionStrategy {
public:
    void resolve(Entity& entity, const Block& block) override
    {
        Rectangle entityRect = entity.getRectangle();
        Rectangle blockRect = block.getHitbox();

        if (CheckCollisionRecs(entityRect, blockRect)) {
            float overlapX = 0;
            float overlapY = 0;
            bool isLeft = 0;
            bool isUp = 0;
            if (entityRect.x < blockRect.x) {
                overlapX = (entityRect.x + entityRect.width) - blockRect.x;
                isLeft = true;
            }
            else {
                overlapX = (blockRect.x + blockRect.width) - entityRect.x;
            }

            if (entityRect.y < blockRect.y) {
                overlapY = (entityRect.y + entityRect.height) - blockRect.y;
                isUp = true;
            }
            else {
                overlapY = (blockRect.y + blockRect.height) - entityRect.y;
            }

            if (std::abs(overlapX) < std::abs(overlapY)) {
                if (overlapX > 0)
                    entity.setPosition(Vector2(entityRect.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX)), entityRect.y));
            }
            else {
                if (overlapY > 0)
                    entity.setPosition(Vector2(entityRect.x, entityRect.y + (isUp ? -std::abs(overlapY) : std::abs(overlapY))));
            }         
        }
    }

    void resolve(Entity& entityA, Entity& entityB) override {}
};
class EntityEntityCollisionHandler : public CollisionStrategy {
public:
    void resolve(Entity& entity, const Block& block) override {}

    void resolve(Entity& entityA, Entity& entityB) override {
        Rectangle rectA = entityA.getRectangle();
        Rectangle rectB = entityB.getRectangle();

        //if (CheckCollisionRecs(rectA, rectB)) 
       //{
       //  do something
       // }
    }
};
class CollisionHandler {
private:
    EntityEntityCollisionHandler entityEntity;
    EntityBlockCollisionHandler entityBlock;
    // add more to this


public:
    void handleCollision(Entity& entityA, Entity& entityB) {
        if (dynamic_cast<Character*>(&entityA) && dynamic_cast<Enemy*>(&entityB)) 
            entityEntity.resolve(entityA, entityB);
        
        //else if (dynamic_cast<Enemy*>(&entityA) && dynamic_cast<Character*>(&entityB)) {
        //    characterEnemyStrategy.handleCollision(entityB, entityA);
        //}
    }

    void handleCollision(Entity& entity, const Block& block) {
        if (dynamic_cast<Character*>(&entity)) 
            entityBlock.resolve(entity, block);
    }
};


