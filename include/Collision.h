#ifndef COLL_H
#define COLL_H
#include "Entity.h"
#include "BaseBlock.h"
#include "Floor.h"
#include "ItemBlock.h"
#include "MovingBlock.h"
#include "SolidBlock.h"
#include "HiddenBlock.h"
#include "PipeBlock.h"
#include "SpikeBlock.h"
#include "Brick.h"
#include "TemporaryBlock.h"
#include "DecorBlock.h"
#include "Character.h"
#include "Enemy.h"
#include "Fireball.h"
#include "Item.h"

class CollisionStrategy {
public:
    virtual bool resolve(Entity* entityA, Entity* entityB) = 0;
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
inline bool shouldCheckCollision(Entity* entityA,  Entity* entityB, float proximityRadius = 20.0f) {
    if (!entityA || !entityB) return false;

    // Calculate proximity bounds for entityA directly
    float leftA = entityA->getX() - proximityRadius;
    float rightA = entityA->getX() + entityA->getWidth() + proximityRadius;
    float topA = entityA->getY() - proximityRadius;
    float bottomA = entityA->getY() + entityA->getHeight() + proximityRadius;

    // Get bounds for entityB
    float leftB = entityB->getX();
    float rightB = entityB->getX() + entityB->getWidth();
    float topB = entityB->getY();
    float bottomB = entityB->getY() + entityB->getHeight();

    // Check for overlap between the expanded rectangle of A and B
    return (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB);
}



class PlayerFloorStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Character* player = dynamic_cast<Character*>(entityA);
        Floor* floor = dynamic_cast<Floor*>(entityB);

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
                Vector2 vector2 = {playerRect.x, floorRect.y - playerRect.height};
                player->setPosition(vector2);
                player->setYVelocity(0.f);
                return true;
            }
        }
     
        return false;

    }
};
class PlayerBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity *entityB) override {
        Character* player = dynamic_cast<Character*>(entityA);
        BaseBlock* block = dynamic_cast<BaseBlock*>(entityB);

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
                    Vector2 vector2 = {blockRect.x - playerRect.width, player->getPosition().y};
                    player->setPosition(vector2);
                }
                else if (velocity.x < 0) {
                    Vector2 vector2 = {blockRect.x + blockRect.width, player->getPosition().y};
                    player->setPosition(vector2);
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
                    Vector2 vector2 = {player->getPosition().x, blockRect.y - playerRect.height};
                    player->setPosition(vector2);
                    player->setYVelocity(0.f);
                    return true;
                }
                else if (velocity.y < 0) {
                    Vector2 vector2 = {player->getPosition().x, blockRect.y + blockRect.height};
                    player->setPosition(vector2);
                    player->setYVelocity(0.f);
                }
            }
        }

        return false;
    }
};

class PlayerItemBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Character* player = dynamic_cast<Character*>(entityA);
        ItemBlock* block = dynamic_cast<ItemBlock*>(entityB); // Assume ItemBlock is a subclass of BaseBlock

        if (!player || !block)
            return false;

        float deltaTime = GetFrameTime();

        Vector2 velocity = player->getVelocity();
        Rectangle playerRect = player->getRectangle();
        Rectangle blockRect = block->getRectangle();

        if (velocity.x != 0) {
            Rectangle horizontalRect = {
                playerRect.x + velocity.x * deltaTime,
                playerRect.y,
                playerRect.width,
                playerRect.height
            };

            if (CheckCollisionRecs(horizontalRect, blockRect)) {
                if (velocity.x > 0) {
                    Vector2 vector2 = {blockRect.x - playerRect.width, player->getPosition().y};
                    player->setPosition(vector2);
                }
                else if (velocity.x < 0) {
                    Vector2 vector2 = {blockRect.x + blockRect.width, player->getPosition().y};
                    player->setPosition(vector2);
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
                    // Player lands on top of the block
                    Vector2 vector2 = {player->getPosition().x, blockRect.y - playerRect.height};
                    player->setPosition(vector2);
                    player->setYVelocity(0.f);
                    return true;
                }
                else if (velocity.y < 0) {
                    Vector2 vector2 = {player->getPosition().x, blockRect.y + blockRect.height};
                    player->setPosition(vector2);
                    player->setYVelocity(0.f);
                    block->releaseItem(player);
                }
            }
        }

        return false;
    }
};

inline bool SweptAABB(const Rectangle& player, const Vector2& playerVel,
    const Rectangle& block, const Vector2& blockVel,
    float deltaTime, float& collisionTime) {
    Vector2 relativeVel = { playerVel.x - blockVel.x, playerVel.y - blockVel.y };

    float xEntry, yEntry;
    float xExit, yExit;

    if (relativeVel.x > 0) {
        xEntry = (block.x - (player.x + player.width)) / relativeVel.x;
        xExit = ((block.x + block.width) - player.x) / relativeVel.x;
    }
    else if (relativeVel.x < 0) {
        xEntry = ((block.x + block.width) - player.x) / relativeVel.x;
        xExit = (block.x - (player.x + player.width)) / relativeVel.x;
    }
    else {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    }

    if (relativeVel.y > 0) {
        yEntry = (block.y - (player.y + player.height)) / relativeVel.y;
        yExit = ((block.y + block.height) - player.y) / relativeVel.y;
    }
    else if (relativeVel.y < 0) {
        yEntry = ((block.y + block.height) - player.y) / relativeVel.y;
        yExit = (block.y - (player.y + player.height)) / relativeVel.y;
    }
    else {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    }

    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

    // If no collision or collision occurs outside the frame
    if (entryTime > exitTime || entryTime < 0.0f || entryTime > deltaTime) {
        collisionTime = 1.0f; // No collision
        return false;
    }

    collisionTime = entryTime;
    return true;
}
class PlayerMovingBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Character* player = dynamic_cast<Character*>(entityA);
        MovingBlock* block = dynamic_cast<MovingBlock*>(entityB);

        if (!player || !block || !player->isCollisionAvailable())
            return false;

        float deltaTime = GetFrameTime();

        Vector2 playerVel = player->getVelocity();
        Vector2 blockVel = block->getVelocity();

        Rectangle playerRect = player->getRectangle();
        Rectangle blockRect = block->getRectangle();

        float collisionTime;
        

        if (!SweptAABB(playerRect, playerVel, blockRect, blockVel, deltaTime, collisionTime)) {
            player->setMovingBlockStandOn(nullptr);
            return false; // No collision detected
        }

        // Calculate the exact position at collision
        Vector2 collisionPlayerPos = {
             playerRect.x + playerVel.x * collisionTime * deltaTime,
            playerRect.y + playerVel.y * collisionTime * deltaTime
        };

        // Adjust player position based on collision direction
        if (playerRect.y + playerRect.height <= blockRect.y) {
            // Player lands on top of the block
            Vector2 vector2 = {playerRect.x, blockRect.y - playerRect.height};
            player->setPosition(vector2);
            player->setYVelocity(0.f); 
            player->setJumping(false);
            player->setMovingBlockStandOn(block);
            return true;    
        }
        else if (playerRect.y >= blockRect.y + blockRect.height) {
            // Player hits the block from below
            Vector2 vector2 = {playerRect.x, blockRect.y + blockRect.height};
            player->setPosition(vector2);
            player->setYVelocity(0.f);
            return false;
        }
        else if (playerRect.x + playerRect.width <= blockRect.x ) {
            // Player hits the block from the left
            Vector2 vector2 = {blockRect.x - playerRect.width, playerRect.y};
            player->setPosition(vector2);
            player->setXVelocity(0.f);
        }
        else if (playerRect.x >= blockRect.x + blockRect.width ) {
            // Player hits the block from the right
            Vector2 vector2 = {blockRect.x + blockRect.width, playerRect.y};
            player->setPosition(vector2);
            player->setXVelocity(0.f);
        }

        //// Follow block movement if the player is on top
        //if (playerRect.y + playerRect.height <= blockRect.y) {
        //    Vector2 newPos = player->getPosition();
        //    newPos.x += blockVel.x * deltaTime; // Move horizontally with block
        //    newPos.y += blockVel.y * deltaTime; // Move vertically with block
        //    player->setPosition(newPos);
        //    player->setJumping(false);
        //}

        return false;
    }
};


class EnemyFloorStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Enemy* enemy = dynamic_cast<Enemy*>(entityA);
        Floor* floor = dynamic_cast<Floor*>(entityB);

        if (!enemy || !floor || enemy->isCollisionAvailable() == false) {
            return false;
        }
        if (enemy->getEnemyType() == PLANT) {
			return false;
        }

        float deltaTime = GetFrameTime();
        Rectangle enemyRect = enemy->getRectangle();
        Rectangle floorRect = floor->getRectangle();
        if (enemy->getVelocity().y > 0.f) {
            Vector2 prevPosition = enemy->getPosition();
            Vector2 nextPosition = {
                prevPosition.x,
                prevPosition.y + enemy->getVelocity().y * deltaTime
            };

            Rectangle sweptRect = {
                prevPosition.x,
                nextPosition.y,
                enemyRect.width,
                enemyRect.height
            };

            if (CheckCollisionRecs(sweptRect, floorRect) && enemy->getBottom() <= floorRect.y){//&& enemy->getBottom() <= floorRect.y) {
                Vector2 vector2 = {enemyRect.x, floorRect.y - enemyRect.height};
                enemy->setPosition(vector2);
                enemy->setYVelocity(0.f);
                enemy->setJumping(false);
                return true;
            }
        }

        return false;
    }
};

class EnemyBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Enemy* enemy = dynamic_cast<Enemy*>(entityA);
        BaseBlock* block = dynamic_cast<BaseBlock*>(entityB);

        if (!enemy || !block || enemy->isCollisionAvailable() == false) {
            return false;
        }
        if (enemy->getEnemyType() == PLANT) {
            return false;
        }
        float deltaTime = GetFrameTime();

        Vector2 velocity = enemy->getVelocity();
        Rectangle enemyRect = enemy->getRectangle();
        Rectangle blockRect = block->getRectangle();

        if (velocity.x != 0) {
            Rectangle horizontalRect = {
                enemyRect.x + velocity.x * deltaTime,
                enemyRect.y,
                enemyRect.width,
                enemyRect.height
            };

            if (CheckCollisionRecs(horizontalRect, blockRect))
            {
                if (velocity.x > 0) {
                    Vector2 vector2 = {blockRect.x - enemyRect.width, enemy->getPosition().y};
                    enemy->setPosition(vector2);
                    enemy->setOrientation(LEFT);
                }
                else if (velocity.x < 0) {
                    Vector2 vector2 = {blockRect.x + blockRect.width, enemy->getPosition().y};
                    enemy->setPosition(vector2);
                    enemy->setOrientation(RIGHT);
                }
                enemy->setXVelocity(0.f);
            }
        }

        if (velocity.y != 0) {
            Rectangle verticalRect = {
                enemyRect.x,
                enemyRect.y + velocity.y * deltaTime,
                enemyRect.width,
                enemyRect.height
            };

            if (CheckCollisionRecs(verticalRect, blockRect)) {
                if (velocity.y > 0) {
                    Vector2 vector2 = {enemy->getPosition().x, blockRect.y - enemyRect.height};
                    enemy->setPosition(vector2);
                    enemy->setYVelocity(0.f);
					enemy->setJumping(false);
                    return true;
                }
                else if (velocity.y < 0) {
                    Vector2 vector2 = {enemy->getPosition().x, blockRect.y + blockRect.height};
                    enemy->setPosition(vector2);
                    enemy->setYVelocity(0.f);
                }
            }
        }
        return false;
    }
};

class PlayerItemStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override
    {
        Character* player = dynamic_cast<Character*>(entityA);
        Item* item = dynamic_cast<Item*>(entityB);

        if (player->isCollisionAvailable() == false || item->isCollisionAvailable() == false)
            return false;

        Rectangle itemRect = item->getRectangle();
        Rectangle playerRect = player->getRectangle();
        if (CheckCollisionRecs(itemRect, playerRect))
        {
            player->collisionWithItem(item);
            item->killEntity();
        }
        return false;
    }
};

class ItemBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Item* item = dynamic_cast<Item*>(entityA);
        BaseBlock* block = dynamic_cast<BaseBlock*>(entityB);

        if (!item || !block || item->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();

        Vector2 velocity = item->getVelocity();
        Rectangle itemRect = item->getRectangle();
        Rectangle blockRect = block->getRectangle();

        if (velocity.x != 0) {
            Rectangle horizontalRect = {
                itemRect.x + velocity.x * deltaTime,
                itemRect.y,
                itemRect.width,
                itemRect.height
            };

            if (CheckCollisionRecs(horizontalRect, blockRect))
            {
                if (velocity.x > 0) {
                    Vector2 vector2 = {blockRect.x - itemRect.width, item->getPosition().y};
                    item->setPosition(vector2);
                    item->setOrientation(LEFT);
                }
                else if (velocity.x < 0) {
                    Vector2 vector2 = {blockRect.x + blockRect.width, item->getPosition().y};
                    item->setPosition(vector2);
                    item->setOrientation(RIGHT);
                }
                item->setXVelocity(0.f);
            }
        }

        if (velocity.y != 0) {
            Rectangle verticalRect = {
                itemRect.x,
                itemRect.y + velocity.y * deltaTime,
                itemRect.width,
                itemRect.height
            };

            if (CheckCollisionRecs(verticalRect, blockRect)) {
                if (velocity.y > 0) {
                    Vector2 vector2 = {item->getPosition().x, blockRect.y - itemRect.height};
                    item->setPosition(vector2);
                    item->setYVelocity(0.f);
                    item->setJumping(false);
                    return true;
                }
                else if (velocity.y < 0) {
                    Vector2 vector2 = {item->getPosition().x, blockRect.y + blockRect.height};
                    item->setPosition(vector2);
                    item->setYVelocity(0.f);
                }
            }
        }
        return false;
    }
};


class PlayerEnemyStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Character* player = dynamic_cast<Character*>(entityA);
        Enemy* enemy = dynamic_cast<Enemy*>(entityB);

        if (!player || !enemy)
            return false;
        if (player->isCollisionAvailable() == false || enemy->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();

        Vector2 playerVelocity = player->getVelocity();
        Vector2 enemyVelocity = enemy->getVelocity();
        Rectangle playerRect = player->getRectangle();
        Rectangle enemyRect = enemy->getRectangle();

        Vector2 playerNextPos = {
            playerRect.x + playerVelocity.x * deltaTime,
            playerRect.y + playerVelocity.y * deltaTime
        };

        Vector2 enemyNextPos = {
            enemyRect.x + enemyVelocity.x * deltaTime,
            enemyRect.y + enemyVelocity.y * deltaTime
        };

        Rectangle futurePlayerRect = {
            playerNextPos.x,
            playerNextPos.y,
            playerRect.width,
            playerRect.height
        };

        Rectangle futureEnemyRect = {
            enemyNextPos.x,
            enemyNextPos.y,
            enemyRect.width,
            enemyRect.height
        };

        bool collisionDetected = CheckCollisionRecs(futurePlayerRect, futureEnemyRect);
        if (!collisionDetected) return false;

        // Top collision (player lands on top of enemy)
        if (playerVelocity.y > 0 && playerRect.y + playerRect.height <= enemyNextPos.y) {
            player->collisionWithEnemy(enemy, TOP_EDGE);
        }
        
        // Bottom collision (player jumps into the enemy from below)
        else if (playerRect.y >= enemyNextPos.y + enemyRect.height) {
            player->collisionWithEnemy(enemy, BOTTOM_EDGE);
        }
        
        // Left collision (player moves into the enemy's right side)
        else if (playerRect.x + playerRect.width <= enemyRect.x) {
            player->collisionWithEnemy(enemy,LEFT_EDGE);
        }
        
        // Right collision (player moves into the enemy's left side)
        else if (playerRect.x >= enemyRect.x + enemyRect.width) {
            player->collisionWithEnemy(enemy, RIGHT_EDGE);
        }

        return false;
    }
};

class ItemFloorStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Item* item = dynamic_cast<Item*>(entityA);
        Floor* floor = dynamic_cast<Floor*>(entityB);

        if (!item || !floor || item->isCollisionAvailable() == false) return false;

        float deltaTime = GetFrameTime();
        Rectangle itemRect = item->getRectangle();
        Rectangle floorRect = floor->getRectangle();
        if (item->getVelocity().y > 0.f) {
            Vector2 prevPosition = item->getPosition();
            Vector2 nextPosition = {
                prevPosition.x,
                prevPosition.y + item->getVelocity().y * deltaTime
            };

            Rectangle sweptRect = {
                prevPosition.x,
                nextPosition.y,
                itemRect.width,
                itemRect.height
            };

            if (CheckCollisionRecs(sweptRect, floorRect) && item->getBottom() <= floorRect.y) {
                Vector2 vector2 = {itemRect.x, floorRect.y - itemRect.height};
                item->setPosition(vector2);
                item->setYVelocity(0.f);
                item->setJumping(false);
                return true;
            }
        }

        return false;

    }
};

class PlayerFireballStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        Character* player = dynamic_cast<Character*>(entityB);

        if (!ball || !player || ball->isCollisionAvailable() == false || player->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();
        Vector2 playerVelocity = player->getVelocity();
        Vector2 ballVelocity = ball->getVelocity();
        Rectangle playerRect = player->getRectangle();
        Rectangle ballRect = ball->getRectangle();

        Vector2 playerNextPos = {
            playerRect.x + playerVelocity.x * deltaTime,
            playerRect.y + playerVelocity.y * deltaTime
        };

        Vector2 ballNextPos = {
            ballRect.x + ballVelocity.x * deltaTime,
            ballRect.y + ballVelocity.y * deltaTime
        };

        Rectangle futurePlayerRect = {
            playerNextPos.x,
            playerNextPos.y,
            playerRect.width,
            playerRect.height
        };

        Rectangle futureBallRect = {
            ballNextPos.x,
            ballNextPos.y,
            ballRect.width,
            ballRect.height
        };

        if (CheckCollisionRecs(futurePlayerRect, futureBallRect)) {
            player->collisionWithFireball(ball);
            return true;
        }

        return false;

    }
};

class EnemyFireballStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        Enemy* enemy = dynamic_cast<Enemy*>(entityB);

        if (!ball || !enemy || ball->isCollisionAvailable() == false || enemy->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();
        Vector2 enemyVelocity = enemy->getVelocity();
        Vector2 ballVelocity = ball->getVelocity();
        Rectangle enemyRect = enemy->getRectangle();
        Rectangle ballRect = ball->getRectangle();

        Vector2 enemyNextPos = {
            enemyRect.x + enemyVelocity.x * deltaTime,
            enemyRect.y + enemyVelocity.y * deltaTime
        };

        Vector2 ballNextPos = {
            ballRect.x + ballVelocity.x * deltaTime,
            ballRect.y + ballVelocity.y * deltaTime
        };

        Rectangle futurePlayerRect = {
            enemyNextPos.x,
            enemyNextPos.y,
            enemyRect.width,
            enemyRect.height
        };

        Rectangle futureBallRect = {
            ballNextPos.x,
            ballNextPos.y,
            ballRect.width,
            ballRect.height
        };

        if (CheckCollisionRecs(futurePlayerRect, futureBallRect)) {
            enemy->collisionWithFireball(ball);
            return true;
        }

        return false;

    }
};

class FireballFloorStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        Floor* floor = dynamic_cast<Floor*>(entityB);

        if (!ball || !floor || ball->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();
        Rectangle ballRect = ball->getRectangle();
        Rectangle floorRect = floor->getRectangle();
        if (ball->getVelocity().y > 0.f) {
            Vector2 prevPosition = ball->getPosition();
            Vector2 nextPosition = {
                prevPosition.x,
                prevPosition.y + ball->getVelocity().y * deltaTime
            };

            Rectangle sweptRect = {
                prevPosition.x,
                nextPosition.y,
                ballRect.width,
                ballRect.height
            };

            if (CheckCollisionRecs(sweptRect, floorRect) && ball->getBottom() <= floorRect.y) {
                Vector2 vector2 = {ballRect.x, floorRect.y - ballRect.height};
                ball->setPosition(vector2);
                ball->collisionWithBlock(floor, TOP_EDGE);
                return true;
            }
        }

        return false;

    }
};

class FireballBlockStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        BaseBlock* block = dynamic_cast<BaseBlock*>(entityB);

        if (!ball || !block || ball->isCollisionAvailable() == false)
            return false;

        if (ball->getFireballType() == PLANT) {
            return false;
        }

        float deltaTime = GetFrameTime();

        Vector2 velocity = ball->getVelocity();
        Rectangle ballRect = ball->getRectangle();
        Rectangle blockRect = block->getRectangle();

        if (velocity.y != 0) {
            Rectangle verticalRect = {
                ballRect.x,
                ballRect.y + velocity.y * deltaTime,
                ballRect.width,
                ballRect.height
            };

            if (CheckCollisionRecs(verticalRect, blockRect)) {
                if (velocity.y > 0) {
                    ball->collisionWithBlock(block, TOP_EDGE);
                    return true;
                }
                else if (velocity.y < 0) {
                    ball->collisionWithBlock(block, BOTTOM_EDGE);
                }
            }
        }

        if (velocity.x != 0) {
            Rectangle horizontalRect = {
                ballRect.x + velocity.x * deltaTime,
                ballRect.y,
                ballRect.width,
                ballRect.height
            };

            if (CheckCollisionRecs(horizontalRect, blockRect)) {
                ball->collisionWithBlock(block, NONE_EDGE);
            }
        }

        return false;
    }
};

class FireballItemBlockStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        ItemBlock* block = dynamic_cast<ItemBlock*>(entityB);

        if (!ball || !block || ball->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();
        Rectangle ballRect = ball->getRectangle();
        Rectangle blockRect = block->getRectangle();
        Vector2 prevPosition = ball->getPosition();
        Vector2 nextPosition = {
            prevPosition.x,
            prevPosition.y + ball->getVelocity().y * deltaTime
        };

        Rectangle sweptRect = {
            prevPosition.x,
            nextPosition.y,
            ballRect.width,
            ballRect.height
        };

        if (CheckCollisionRecs(sweptRect, blockRect)) {
            ball->collisionWithBlock(block, NONE_EDGE);
            block->releaseItem(ball);
            return true;
        }

        return false;

    }
};

class FireballBrickStrat : public CollisionStrategy
{
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Fireball* ball = dynamic_cast<Fireball*>(entityA);
        Brick* block = dynamic_cast<Brick*>(entityB);

        if (!ball || !block || ball->isCollisionAvailable() == false)
            return false;

        float deltaTime = GetFrameTime();
        Rectangle ballRect = ball->getRectangle();
        Rectangle blockRect = block->getRectangle();
        Vector2 prevPosition = ball->getPosition();
        Vector2 nextPosition = {
            prevPosition.x,
            prevPosition.y + ball->getVelocity().y * deltaTime
        };

        Rectangle sweptRect = {
            prevPosition.x,
            nextPosition.y,
            ballRect.width,
            ballRect.height
        };

        if (CheckCollisionRecs(sweptRect, blockRect)) {
            ball->collisionWithBlock(block, NONE_EDGE);
            block->breakBrick();
            return true;
        }

        return false;

    }
};



class EnemyEmenyStrat : public CollisionStrategy {
public:
    bool resolve(Entity* entityA, Entity* entityB) override {
        Enemy* enemy1 = dynamic_cast<Enemy*>(entityA);
        Enemy* enemy2 = dynamic_cast<Enemy*>(entityB);

        if (!enemy1 || !enemy2 || enemy1->isCollisionAvailable() == false || enemy2->isCollisionAvailable() == false)
            return false;
        if (enemy1->getEnemyType() != SHELL) return false;


        float deltaTime = GetFrameTime();

        Vector2 enemy1Velocity = enemy1->getVelocity();
        Vector2 enemy2Velocity = enemy2->getVelocity();
        Rectangle enemy1Rect = enemy1->getRectangle();
        Rectangle enemy2Rect = enemy2->getRectangle();

        Vector2 enemy1NextPos = {
            enemy1Rect.x + enemy1Velocity.x * deltaTime,
            enemy1Rect.y + enemy1Velocity.y * deltaTime
        };

        Vector2 enemy2NextPos = {
            enemy2Rect.x + enemy2Velocity.x * deltaTime,
            enemy2Rect.y + enemy2Velocity.y * deltaTime
        };

        Rectangle future1 = {
            enemy1NextPos.x,
            enemy1NextPos.y,
            enemy1Rect.width,
            enemy1Rect.height
        };

        Rectangle future2 = {
            enemy2NextPos.x,
            enemy2NextPos.y,
            enemy2Rect.width,
            enemy2Rect.height
        };

        if (CheckCollisionRecs(future1, future2)) {
            
            return true;
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
            if (block && block->getBlockType() == MOVINGBLOCK)
                return std::make_unique<PlayerMovingBlockStrat>();
            if (block && block->getBlockType() == ITEMBLOCK)
                return std::make_unique<PlayerItemBlockStrat>();
            //if (block && block->getBlockType() == SOLIDBLOCK)
            return std::make_unique<PlayerBlockStrat>();
        }
        if (typeA == ENEMY && typeB == BLOCK)
        {
            if (block && block->getBlockType() == FLOOR)
                return make_unique<EnemyFloorStrat>();
            if (block && block->getBlockType() == SOLIDBLOCK)
                return make_unique<EnemyBlockStrat>();
            return make_unique<EnemyBlockStrat>();
        }
        if (typeA == CHARACTER && typeB == ENEMY)
        {
            return make_unique<PlayerEnemyStrat>();
        }
        if (typeA == CHARACTER && typeB == ITEM)
        {
            return std::make_unique<PlayerItemStrat>();
        }
        if (typeA == ITEM && typeB == BLOCK)
        {
            if (block && block->getBlockType() == FLOOR)
                return std::make_unique<ItemFloorStrat>();
            //if (block && block->getBlockType() == SOLIDBLOCK)
            return std::make_unique<ItemBlockStrat>();

        }

        if (typeA == FIREBALL && typeB == CHARACTER) {
            return std::make_unique<PlayerFireballStrat>();
        }
        if (typeA == FIREBALL && typeB == ENEMY) {
            return std::make_unique<EnemyFireballStrat>();
        }
        if (typeA == FIREBALL && typeB == BLOCK) {
            if (block && block->getBlockType() == FLOOR) {
                return std::make_unique<FireballFloorStrat>();
            }
            if (block && block->getBlockType() == ITEMBLOCK) {
                return std::make_unique<FireballItemBlockStrat>();
            }
            if (block && block->getBlockType() == BRICK) {
                return std::make_unique<FireballBrickStrat>();
            }
            return std::make_unique<FireballBlockStrat>();
        }
        if (typeA == ENEMY && typeB == ENEMY) {

        }


        return nullptr; 
    }
};


class CollisionInterface {
public:
    bool resolve(Entity* entityA, Entity* entityB) {
        if (!shouldCheckCollision(entityA, entityB)) {
            return false;
        }
        auto typeA = entityA->getType();
        auto typeB = entityB->getType();

        BaseBlock* block = dynamic_cast<BaseBlock*>(entityB);
        auto strategy = CollisionStrategySelector::getStrategy(typeA, typeB, block);
        if (!strategy) {
            strategy = CollisionStrategySelector::getStrategy(typeB, typeA, dynamic_cast<BaseBlock*>(entityA));
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
#endif