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
inline bool shouldCheckCollision(const Entity& entityA, const Entity& entityB, float proximityRadius = 20.0f) {
    // Calculate proximity bounds for entityA directly
    float leftA = entityA.getX() - proximityRadius;
    float rightA = entityA.getX() + entityA.getWidth() + proximityRadius;
    float topA = entityA.getY() - proximityRadius;
    float bottomA = entityA.getY() + entityA.getHeight() + proximityRadius;

    // Get bounds for entityB
    float leftB = entityB.getX();
    float rightB = entityB.getX() + entityB.getWidth();
    float topB = entityB.getY();
    float bottomB = entityB.getY() + entityB.getHeight();

    // Check for overlap between the expanded rectangle of A and B
    return (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB);
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
                if (velocity.x > 0) {
                    player->setPosition(Vector2(blockRect.x - playerRect.width, player->getPosition().y));
                    cout << "aaaaaa\n";
                }
                else if (velocity.x < 0) {
                    player->setPosition(Vector2(blockRect.x + blockRect.width, player->getPosition().y));
                    cout << "BBBBBB\n";
                }
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
                    player->setPosition(Vector2(player->getPosition().x, blockRect.y - playerRect.height));
                    player->setYVelocity(0.f);
                    return true;
                }
                else if (velocity.y < 0) { 
                    player->setPosition(Vector2(player->getPosition().x, blockRect.y + blockRect.height));
                    player->setYVelocity(0.f);
                }
            }
        }

        return false;
    }
};

class PlayerMovingBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity& entityA, Entity& entityB) override {
        Character* player = dynamic_cast<Character*>(&entityA);
        MovingBlock* block = dynamic_cast<MovingBlock*>(&entityB);

        if (!player || !block)
            return false;

        float deltaTime = GetFrameTime();

        Vector2 blockVelocity = block->getVelocity();
        Vector2 playerVelocity = player->getVelocity();
        Rectangle playerRect = player->getRectangle();
        Rectangle blockRect = block->getRectangle();

        Vector2 playerNextPos = {
            playerRect.x + playerVelocity.x * deltaTime,
            playerRect.y + playerVelocity.y * deltaTime
        };

        Rectangle futurePlayerRect = {
            playerNextPos.x,
            playerNextPos.y,
            playerRect.width,
            playerRect.height
        };

        bool isOnBlock = false;

        // vertical collision detection (falling onto the block)
        if (playerVelocity.y >= 0) {
            if (CheckCollisionRecs(futurePlayerRect, blockRect) && player->getBottom() <= blockRect.y) {
                player->setPosition(Vector2(playerRect.x, blockRect.y - playerRect.height));
                player->setYVelocity(0.f);
                isOnBlock = true;
            }
        }

        // horizontal
        Rectangle horizontalRect = {
            playerNextPos.x,
            playerRect.y,
            playerRect.width,
            playerRect.height
        };

        if (CheckCollisionRecs(horizontalRect, blockRect)) {
            if (playerVelocity.x > 0) {
                float offset = blockVelocity.x * deltaTime;
                player->setPosition(Vector2(blockRect.x - playerRect.width + offset, playerRect.y));
            }
            else if (playerVelocity.x < 0) {
                float offset = blockVelocity.x * deltaTime;
                player->setPosition(Vector2(blockRect.x + blockRect.width + offset, playerRect.y));
            }
            player->setXVelocity(0.f);
        }

        if (playerVelocity.y < 0) { // Jumping into the block from below
            Rectangle verticalRect = {
                playerRect.x,
                playerNextPos.y,
                playerRect.width,
                playerRect.height
            };

            if (CheckCollisionRecs(verticalRect, blockRect) && player->getTop() >= blockRect.y + blockRect.height) {
                player->setPosition(Vector2(playerRect.x, blockRect.y + blockRect.height));
                player->setYVelocity(0.f);
            }
        }

        if (isOnBlock) {
            Vector2 newPos = player->getPosition();
            newPos.x += blockVelocity.x * deltaTime; // Move horizontally with block
            newPos.y += blockVelocity.y * deltaTime; // Move vertically with block
            player->setPosition(newPos);
        }

        return isOnBlock;
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
        if (typeA == CHARACTER && typeB == BLOCK) {
            if (block && block->getBlockType() == FLOOR)
                return std::make_unique<PlayerFloorStrat>();
            if(block && block->getBlockType() == MOVINGBLOCK)
                return std::make_unique<PlayerMovingBlockStrat>();
            //if (block && block->getBlockType() == SOLIDBLOCK)
            return std::make_unique<PlayerBlockStrat>();
        }
        if (typeA == ENEMY && typeB == BLOCK)
        {
            if (block && block->getBlockType() == SOLIDBLOCK)
                return make_unique<EnemyBlockStrat>();
        }
        if (typeA == CHARACTER && typeB == ENEMY)
        {

        }
        if (typeA == CHARACTER && ITEM)
        {

        }



        return nullptr; 
    }
};
class CollisionInterface {
public:
    bool resolve(Entity& entityA, Entity& entityB) {
        if (!shouldCheckCollision(entityA, entityB)) {
            return false;
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