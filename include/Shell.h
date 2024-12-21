#pragma once
#include "Enemy.h"

class Shell :public Enemy {
private:
	ShellType type;
	Animation* inShell;
	Animation* outShell;
	Animation* shellSpin;
	
	bool isKicked;
	bool isHold;
	float inShellTime;

	const float IN_SHELL_TIME = 5.f;
	const float OUT_SHELL_TIME = 1.f;
	const float SPIN_SPEED = 300.f;
public:
	~Shell() {
		free(inShell);
		free(outShell);
		free(shellSpin);
		inShell = nullptr;
		outShell = nullptr;
		shellSpin = nullptr;
	}

	Shell(ShellType type = GREEN_SHELL, Vector2 position = { 0.f, 0.f }) : Enemy(position) {
		this->type = type;
		this->inShellTime = 0.f;
		this->isKicked = false;
		this->isHold = false;
		inShell = nullptr;
		outShell = nullptr;
		shellSpin = nullptr;

		if (type == GREEN_SHELL) {
			inShell = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_shell")->clone();
			outShell = RESOURCE_MANAGER.getAnimation("green_KoopaTroopa_outShell")->clone();
			shellSpin = RESOURCE_MANAGER.getAnimation("green_paraKoopaTroopa_spin")->clone();
		}
		else if (type == RED_SHELL) {
			inShell = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_shell")->clone();
			outShell = RESOURCE_MANAGER.getAnimation("red_KoopaTroopa_outShell")->clone();
			shellSpin = RESOURCE_MANAGER.getAnimation("red_paraKoopaTroopa_spin")->clone();
		}

		setAnimation(inShell);
	}

	EnemyType getEnemyType() const override {
		return EnemyType::SHELL;
	}

	void update(float deltaTime) override {
		if (isDead()) return;
		if (inShellTime >= IN_SHELL_TIME) {
			killEntity();
			//Create an Koopa Troopa 
			return;
		}	

		if (isKicked) inShellTime = 0.f;
		else inShellTime += deltaTime;

		if (getPosition().x <= getBoundary().x) setOrientation(RIGHT);
		else if (getPosition().x >= getBoundary().y) setOrientation(LEFT);

		if (isGravityAvailable()) setYVelocity(velocity.y + GRAVITY * deltaTime);
		if (isKicked) {
			if (orientation) setXVelocity(SPIN_SPEED);
			else setXVelocity(-SPIN_SPEED);
			setAnimation(shellSpin);
		}
		else {
			setXVelocity(0.f);
			if (inShellTime < IN_SHELL_TIME - OUT_SHELL_TIME) {
				setAnimation(inShell);
			}
		}

		//TEST
		//if (getBottom() >= 500.f) {
		//	setYVelocity(0.f);
		//	setYPosition(500.f - getSize().y);
		//	jumping = false;
		//}

		if (inShellTime >= IN_SHELL_TIME - OUT_SHELL_TIME) {
			setAnimation(outShell);
		}
	}

	void kicked(Orientation direction) override {
			setOrientation(direction);
			isKicked = true;
	}

	void stomped(Vector2 center) {
		if (isKicked == true) {
			isKicked = false;
			return;
		}

		if (getCenter().x > center.x) {
			setOrientation(RIGHT);
		}
		else {
			setOrientation(LEFT);
		}
		isKicked = true;
	}
};