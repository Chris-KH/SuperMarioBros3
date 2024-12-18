﻿#pragma once
#include"Entity.h"
#include"Block.h"
#include"Character.h"
#include"Enemy.h"

class CollisionStrategy {
public:
    virtual bool resolve(Entity& entityA, Entity& entityB) = 0;
    virtual ~CollisionStrategy() = default;
};

inline Rectangle getProximityRectangle(Entity& entity, float radius) {
    Rectangle rect = entity.getRectangle();
    return {
        rect.x - radius,
        rect.y - radius,
        rect.width + 2 * radius,
        rect.height + 2 * radius
    };
}
inline bool shouldCheckCollision(Entity& entityA, Entity& entityB, float proximityRadius = 40.0f) {
    Rectangle proximityRectA = getProximityRectangle(entityA, proximityRadius);
    Rectangle proximityRectB = entityB.getRectangle(); // Unmovable entities stay static

    // Check if proximity rectangles overlap
    return CheckCollisionRecs(proximityRectA, proximityRectB);
}


class PlayerFloorStrat : public CollisionStrategy
{
public:
    bool resolve(Entity& entityA, Entity& entityB) override {
        Character* player = dynamic_cast<Character*>(&entityA);
        Floor* floor = dynamic_cast<Floor*>(&entityB);

        if (!player || !floor)
            return false;
        float deltaTime = GetFrameTime();
        Rectangle playerRect = player->getRectangle();
        Rectangle floorRect = floor->getRectangle();
        if (player->getVelocity().y > 0.f) {
            Vector2 prevPosition = player->getPosition();
            Vector2 nextPosition = {
                prevPosition.x,
                prevPosition.y + player->getVelocity().y * deltaTime
            };

            Rectangle sweptRect = {
                prevPosition.x,
                nextPosition.y,
                playerRect.width,
                playerRect.height
            };

            if (CheckCollisionRecs(sweptRect, floorRect) && player->getBottom() <= floorRect.y) {
                player->setPosition(Vector2(playerRect.x, floorRect.y - playerRect.height));
                player->setYVelocity(0.f);
                return true;
            }
        }
     
        return false;

    }
};
class PlayerBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity& entityA, Entity& entityB) override {
        Character* player = dynamic_cast<Character*>(&entityA);
        BaseBlock* block = dynamic_cast<BaseBlock*>(&entityB);

        if (!player || !block)
            return false;

        float deltaTime = GetFrameTime();

        Vector2 velocity = player->getVelocity();
        Rectangle playerRect = player->getRectangle();
        Rectangle blockRect = block->getRectangle();

        // thay vì để 1 future rect, chia 2 trường hợp để dễ check hơn.

        if (velocity.x != 0) {
            Rectangle horizontalRect = {
                playerRect.x + velocity.x * deltaTime,
                playerRect.y,
                playerRect.width,
                playerRect.height
            };

            if (CheckCollisionRecs(horizontalRect, blockRect)) 
            {
                if (velocity.x > 0)
                    player->setPosition(Vector2(blockRect.x - playerRect.width, playerRect.y));
                else if (velocity.x < 0) 
                    player->setPosition(Vector2(blockRect.x + blockRect.width, playerRect.y));
                player->setXVelocity(0.f); 
            }
        }

        if (velocity.y != 0) {
            Rectangle verticalRect = {
                playerRect.x,
                playerRect.y + velocity.y * deltaTime,
                playerRect.width,
                playerRect.height
            };

            if (CheckCollisionRecs(verticalRect, blockRect)) {
                if (velocity.y > 0) {
                    player->setPosition(Vector2(playerRect.x, blockRect.y - playerRect.height));
                    player->setYVelocity(0.f);
                    return true;
                }
                else if (velocity.y < 0) { 
                    player->setPosition(Vector2(playerRect.x, blockRect.y + blockRect.height));
                    player->setYVelocity(0.f);
                }
            }
        }

        return false;
    }
};



class EnemyBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity& enemy, Entity& block) override {
        Rectangle enemyRect = enemy.getRectangle();
        Rectangle blockRect = block.getRectangle();

        if (CheckCollisionRecs(enemyRect, blockRect)) {
            float overlapX = 0;
            float overlapY = 0;
            bool isLeft = false;
            bool isUp = false;

            if (enemyRect.x < blockRect.x) {
                overlapX = (enemyRect.x + enemyRect.width) - blockRect.x;
                isLeft = true;
            }
            else
                overlapX = (blockRect.x + blockRect.width) - enemyRect.x;
            if (enemyRect.y < blockRect.y) {
                overlapY = (enemyRect.y + enemyRect.height) - blockRect.y;
                isUp = true;
            }
            else 
                overlapY = (blockRect.y + blockRect.height) - enemyRect.y;
            if (std::abs(overlapX) < std::abs(overlapY)) {
                Vector2 vector2 = {enemyRect.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX)), enemyRect.y};
                enemy.setPosition(vector2);
            } else {
                Vector2 vector2 = {enemyRect.x, enemyRect.y + ((isUp) ? -std::abs(overlapY) : std::abs(overlapY))};
                enemy.setPosition(vector2);
            }
        }
        return false;
    }
};

class CollisionStrategySelector {
public:
    static std::unique_ptr<CollisionStrategy> getStrategy(EntityType typeA, EntityType typeB, BaseBlock* block = nullptr) {
        if (typeA == CHACRACTER && typeB == BLOCK) {
            if (block && block->getBlockType() == FLOOR)
                return std::make_unique<PlayerFloorStrat>();
            if (block && block->getBlockType() == SOLIDBLOCK)
                return std::make_unique<PlayerBlockStrat>();
        }
        if (typeA == ENEMY && typeB == BLOCK)
        {
            if (block && block->getBlockType() == SOLIDBLOCK)
                return make_unique<EnemyBlockStrat>();
        }
        if (typeA == CHACRACTER && typeB == ENEMY)
        {

        }
        if (typeA == CHACRACTER && ITEM)
        {

        }



        return nullptr; // No applicable strategy
    }
};
class CollisionInterface {
public:
    bool resolve(Entity& entityA, Entity& entityB) {
        if (!shouldCheckCollision(entityA, entityB)) {
            return false; // Skip unnecessary checks
        }
        auto typeA = entityA.getType();
        auto typeB = entityB.getType();

        BaseBlock* block = dynamic_cast<BaseBlock*>(&entityB);
        auto strategy = CollisionStrategySelector::getStrategy(typeA, typeB, block);
        if (!strategy) {
            strategy = CollisionStrategySelector::getStrategy(typeB, typeA, dynamic_cast<BaseBlock*>(&entityA));
        }
        if (strategy) {
            return strategy->resolve(entityA, entityB);
        }
        else {
            std::cout << "No collision strategy found for entities: "
                << static_cast<int>(typeA) << " and " << static_cast<int>(typeB) << std::endl;
        }
        return false;
    }

};