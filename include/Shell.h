#ifndef SHELL_H
#define SHELL_H

#include "Enemy.h"

class GameEngine;
class Character;

class Shell :public Enemy {
private:
	ShellType type;
	Animation* inShell;
	Animation* outShell;
	Animation* shellSpin;
	
	bool isKicked;
	bool isHold;
	float inShellTime;

	const float IN_SHELL_TIME = 100.f;
	const float OUT_SHELL_TIME = 3.f;
	const float SPIN_SPEED = 200.f;
public:
	~Shell();

	Shell(ShellType type = GREEN_SHELL, Vector2 position = { 0.f, 0.f });

	EnemyType getEnemyType() const override;

	void update(float deltaTime) override;
	void setIsHold(bool hold);
	bool getIsHold() const;
	void setIsKicked(bool kicked);
	bool getIsKicked() const;
	void kicked(Orientation direction = RIGHT) override;
	void stomped(Vector2 center = { 0.f, 0.f });
	void attacked(Orientation direction = RIGHT) override;

	void setHoldingPosition(const Character* character);
};
#endif