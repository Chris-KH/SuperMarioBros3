#include "../include/Enemy.h"
#include "../include/Character.h"

Enemy::Enemy(Vector2 pos, Vector2 size, Color col) {
    stompable = false;
    kickable = false;
    jumping = false;

    boudary = { 0.f, 3000.f };
    setPosition(pos);
};

EntityType Enemy::getType() const { return EntityType::ENEMY; }

void Enemy::draw(float deltaTime) {
    if (isDead()) return;

    if (currentAnimation == nullptr) return;
    setXPosition(getPosition().x + velocity.x * deltaTime);
    setYPosition(getPosition().y + velocity.y * deltaTime);
    currentAnimation->update(deltaTime);
    currentAnimation->render(getPosition());
}

void Enemy::update(float deltaTime) {
    currentAnimation->update(deltaTime);
    if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);

    if (isJumping()) {
        setYPosition(getPosition().y + velocity.y * deltaTime);
    }

    if (getBottom() >= 500.f) {
        setYVelocity(0.f);
        setYPosition(500.f - getSize().y);
        jumping = false;
    }
}

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
}