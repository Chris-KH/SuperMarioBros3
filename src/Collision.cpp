//#include "../include/Collision.h"
//#include "../include/Entity.h"
//#include "../include/Block.h"
//#include "../lib/raylib.h"
//#include <cmath>
//
//bool EntityToBlockPushbackCollision::collides(Entity& entity, const Block& block) {
//    Rectangle entityHitbox = entity.getHitBox();
//    Rectangle blockHitbox = block.getHitbox();
//
//    if (CheckCollisionRecs(entityHitbox, blockHitbox)) {
//        float overlapX = 0;
//        float overlapY = 0;
//        bool isLeft = 0;
//        bool isUp = 0;
//        if (entityHitbox.x < blockHitbox.x) {
//            overlapX = (entityHitbox.x + entityHitbox.width) - blockHitbox.x;
//            isLeft = true;
//        }
//        else {
//            overlapX = (blockHitbox.x + blockHitbox.width) - entityHitbox.x;
//        }
//
//        if (entityHitbox.y < blockHitbox.y) {
//            overlapY = (entityHitbox.y + entityHitbox.height) - blockHitbox.y;
//            isUp = true;
//        }
//        else {
//            overlapY = (blockHitbox.y + blockHitbox.height) - entityHitbox.y;
//        }
//
//        if (std::abs(overlapX) < std::abs(overlapY)) {
//            if (overlapX > 0)         
//                entity.setPosition(Vector2(entityHitbox.x + ((isLeft) ? -std::abs(overlapX) : std::abs(overlapX)), entityHitbox.y));         
//        }
//        else {
//            if (overlapY > 0)
//                entity.setPosition(Vector2(entityHitbox.x, entityHitbox.y + (isUp ? -std::abs(overlapY) : std::abs(overlapY))));
//        }
//        return true;
//    }
//    return false;
//}
////
////bool EntityToBlockPushbackCollision::collides(Entity& entity, const Block& block)
////{
////    if (CheckCollisionRecs(entity.hitbox, block.hitbox)) {
////        float overlapX = 0;
////        float overlapY = 0;
////        bool isLeft = 0;
////        bool isUp = 0;
////        if (entity.hitbox.x < block.hitbox.x) {
////            overlapX = (entity.hitbox.x + entity.hitbox.width) - block.hitbox.x;
////            isLeft = true;
////        }
////        else {
////            overlapX = (block.hitbox.x + block.hitbox.width) - entity.hitbox.x;
////        }
////
////        if (entity.hitbox.y < block.hitbox.y) {
////            overlapY = (entity.hitbox.y + entity.hitbox.height) - block.hitbox.y;
////            isUp = true;
////        }
////        else {
////            overlapY = (block.hitbox.y + block.hitbox.height) - entity.hitbox.y;
////        }
////
////        // Push back along the smallest overlap to resolve the collision
////        if (std::abs(overlapX) < std::abs(overlapY)) {
////            // Push back along the X-axis
////            if (overlapX > 0)
////                entity.hitbox.x += (isLeft) ? -std::abs(overlapX) : std::abs(overlapX);
////        }
////        else {
////            // Push back along the Y-axis
////            if (overlapY > 0)
////                entity.hitbox.y += (isUp) ? -std::abs(overlapY) : std::abs(overlapY);
////        }
////
////        return true;
////    }
////    return false;
////}
//
//bool EntityToBLockCollision::collides(Entity& entity, const Block& block)
//{
//    Rectangle entityHitbox = entity.getHitBox();
//    Rectangle blockHitbox = block.getHitbox();
//    return CheckCollisionRecs(entityHitbox, blockHitbox);
//}
