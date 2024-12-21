#pragma once
#include "Enemy.h"

class GameEngine;

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
	~Shell();

	Shell(ShellType type = GREEN_SHELL, Vector2 position = { 0.f, 0.f });

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;
	void kicked(Orientation direction = RIGHT) override;
	void stomped(Vector2 center = { 0.f, 0.f });
};