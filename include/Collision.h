#pragma once
#include"Entity.h"
#include"Block.h"
#include"Character.h"
#include"Enemy.h"
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
class CollisionLogicHandler {
public:
    void resolve(Entity& entityA, Entity& entityB) {
        auto typeA = entityA.getType();
        auto typeB = entityB.getType();

        BaseBlock* block = dynamic_cast<BaseBlock*>(&entityB);
        auto strategy = CollisionStrategySelector::getStrategy(typeA, typeB, block);
        if (!strategy) {
            strategy = CollisionStrategySelector::getStrategy(typeB, typeA, dynamic_cast<BaseBlock*>(&entityA));
        }
        if (strategy) {
            strategy->resolve(entityA, entityB);
        }
        else {
            std::cout << "No collision strategy found for entities: "
                << static_cast<int>(typeA) << " and " << static_cast<int>(typeB) << std::endl;
        }
    }
};



class CollisionStrategy {
public:
    virtual void resolve(Entity& entityA, Entity& entityB) = 0;
    virtual ~CollisionStrategy() = default;
};
class PlayerFloorStrat : public CollisionStrategy
{
public:
    void resolve(Entity& entityA, Entity& entityB) override
    {
        Floor* floor = dynamic_cast<Floor*>(&entityB);
        Character* player = dynamic_cast<Character*>(&entityA);

        if (!floor || !player)
            return;

        Rectangle playerRect = player->getRectangle();
        Rectangle floorRect = floor->getRectangle();

        Vector2 playerVelocity = player->getVelocity();
        Rectangle futurePlayerRect = {
            playerRect.x,
            playerRect.y + playerVelocity.y,
            playerRect.width,
            playerRect.height
        };

        if (CheckCollisionRecs(futurePlayerRect, floorRect)) {
            // Ensure the player was above the floor in the previous frame
            if (playerRect.y + playerRect.height <= floorRect.y) {
                // Snap the player to the top of the floor
                player->setPosition(Vector2(playerRect.x, floorRect.y - playerRect.height));

                // Reset vertical velocity to prevent falling
                player->setVelocity(Vector2(playerVelocity.x, 0));
            }
        }
    }

};
class PlayerBlockStrat : public CollisionStrategy {
public:
    void resolve(Entity& player, Entity& block) override {
        Rectangle playerRect = player.getRectangle();
        Rectangle blockRect = block.getRectangle();

        if (CheckCollisionRecs(playerRect, blockRect)) {
            float overlapX = 0;
            float overlapY = 0;
            bool isLeft = false;
            bool isUp = false;
            if (playerRect.x < blockRect.x) {
                overlapX = (playerRect.x + playerRect.width) - blockRect.x;
                isLeft = true;
            }
            else 
                overlapX = (blockRect.x + blockRect.width) - playerRect.x;
            if (playerRect.y < blockRect.y) {
                overlapY = (playerRect.y + playerRect.height) - blockRect.y;
                isUp = true;
            }
            else 
                overlapY = (blockRect.y + blockRect.height) - playerRect.y;
            if (std::abs(overlapX) < std::abs(overlapY)) 
                player.setPosition(Vector2(playerRect.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX)), playerRect.y));
            else if (isUp)
                player.setPosition(Vector2(playerRect.x, playerRect.y - std::abs(overlapY)));
        }
    }
};
class EnemyBlockStrat : public CollisionStrategy {
public:
    void resolve(Entity& enemy, Entity& block) override {
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
    }
};


