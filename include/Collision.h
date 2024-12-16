#pragma once
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
        if (CheckCollisionRecs(playerRect, floorRect)) {
            if (playerRect.y + playerRect.height <= floorRect.y + 5.f && player->getVelocity().y >= 0.f) {
                player->setPosition(Vector2(playerRect.x, floorRect.y - playerRect.height + 0.005f));
                player->setYVelocity(0.f);
                return true;
            }
        }
        if (player->getVelocity().y >= 800.f) {
            Vector2 prevPosition = player->getPosition();
            Vector2 nextPosition = {
                prevPosition.x,
                prevPosition.y + player->getVelocity().y * deltaTime
            };

            Rectangle sweptRect = {
                prevPosition.x,
                prevPosition.y,
                playerRect.width,
                nextPosition.y - prevPosition.y
            };

            if (CheckCollisionRecs(sweptRect, floorRect)) {
                player->setPosition(Vector2(playerRect.x, floorRect.y - playerRect.height + 0.005f));
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

        Rectangle playerRect = player->getRectangle();
        Rectangle blockRect = block->getRectangle();

        if (CheckCollisionRecs(playerRect, blockRect)) {
            float overlapX = 0.f;
            float overlapY = 0.f;
            bool isLeft = false;
            bool isUp = false;

            if (playerRect.x < blockRect.x) {
                overlapX = (playerRect.x + playerRect.width) - blockRect.x;
                isLeft = true;
            }
            else {
                overlapX = (blockRect.x + blockRect.width) - playerRect.x;
            }

            if (playerRect.y < blockRect.y) {
                overlapY = (playerRect.y + playerRect.height) - blockRect.y;
                isUp = true;
            }
            else {
                overlapY = (blockRect.y + blockRect.height) - playerRect.y;
            }
            Vector2 velocity = player->getVelocity();
            if (std::abs(overlapX) < std::abs(overlapY) || velocity.y < 0 && isUp) {
                float newPosX = playerRect.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX));
                player->setPosition(Vector2(newPosX, playerRect.y));

                player->setVelocity(Vector2(0, player->getVelocity().y));
            }
            else {
                float newPosY = playerRect.y + ((isUp) ? (-std::abs(overlapY) + 0.005f) : std::abs(overlapY));
                player->setPosition(Vector2(playerRect.x, newPosY));
                if (isUp) {
                    player->setVelocity(Vector2(player->getVelocity().x, 0.f));
                    return true;
                }
                else {
                    player->setVelocity(Vector2(player->getVelocity().x, -(player->getVelocity().y) / 4));
                }
                return false;
            }
            return false;
        }

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
            if (std::abs(overlapX) < std::abs(overlapY)) 
                enemy.setPosition(Vector2(enemyRect.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX)), enemyRect.y));
            else 
                enemy.setPosition(Vector2(enemyRect.x, enemyRect.y + ((isUp) ? -std::abs(overlapY) : std::abs(overlapY))));
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