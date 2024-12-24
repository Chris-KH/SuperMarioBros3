#include "../include/Enemy.h"
#include "../include/Character.h"
#include "../include/GameEngine.h"
#include "../include/Effect.h"
#include "../include/TextEffect.h"
#include "../include/Fireball.h"

Enemy::Enemy(Vector2 pos, Vector2 size) {
    stompable = false;
    kickable = false;
    jumping = false;

    boudary = { 0.f, 3000.f };
    setPosition(pos);
};

EntityType Enemy::getType() const { return EntityType::ENEMY; }

Orientation Enemy::getRandomOrientation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 1);

    if (distr(gen) % 2 == 0) return RIGHT;
    return LEFT;
}

void Enemy::setBoudary(Vector2 boudary) {
    this->boudary = boudary;
}

const Vector2& Enemy::getBoundary() const {
    return boudary;
}

void Enemy::stomped() {

}

void Enemy::attacked() {
    if (isDead()) return;
    killEntity();
    setCollisionAvailable(false);

    Effect* text = new TextEffect(to_string(ENEMY_POINT).c_str(), getCenter());
    globalGameEngine->addEffect(text);
}

void Enemy::collisionWithFireball(Fireball* fireball) {
    attacked();
    fireball->setCollisionAvailable(false);
    fireball->killEntity();
    setCollisionAvailable(false);
    Effect* smoke = new Effect(RESOURCE_MANAGER.getAnimation("smoke")->clone(), getPosition(), true, 0.f);
    smoke->setGravityAvailable(false);
    globalGameEngine->addEffect(smoke);
    RESOURCE_MANAGER.playSound("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Sound/fireball.wav");
}