#include "../include/Entity.h"

Rectangle Entity::getHitBox() {
    return Rectangle(position.x, position.y, size.x, size.y);
}

void Entity::setPosition(Vector2 newPos) { position = newPos; }

void Entity::handleInput() {
    velocity = { 0, 0 };
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) velocity.x += speed;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) velocity.x -= speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) velocity.y += speed;
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) velocity.y -= speed;

    if (velocity.x < 0) {
        isFlipped = true;  // Flip 180 degree to the left
    }
    else if (velocity.x > 0) {
        isFlipped = false;
    }
}

void Entity::move() {
    float deltaTime = GetFrameTime();
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Entity::draw()  {
    Vector2 origin = { 0, 0 };

    // Flip sourceRect width to mirror the image when isFlipped is true
    Rectangle flippedSourceRect = sourceRect;
    flippedSourceRect.width = isFlipped ? -sourceRect.width : sourceRect.width;

    Rectangle destRect = { position.x, position.y, size.x, size.y };
    DrawTexturePro(texture, flippedSourceRect, destRect, origin, 0.0f, WHITE);
    //Rectangle temp = getHitBox();
    //DrawRectangleRec(temp, RED);
}

void Entity::unloadTexture() const {
    UnloadTexture(texture);
}

void Entity::setCollisionStrategy(ICollisionStrategy* strategy)
{
    collisionStrategy = strategy;
}

bool Entity::checkCollision(const Block& block)
{
    if (collisionStrategy)
        return collisionStrategy->collides(*this, block);
    return false;
}
