#pragma once
#include"Sprite.h"

class Fireball: public Sprite {
private:
	Animation* fireRight;
	Animation* fireLeft;
public:
	~Fireball() {
		free(fireRight);
		free(fireLeft);
		fireLeft = nullptr;
		fireRight = nullptr;
	}

	Fireball() {

	}
};