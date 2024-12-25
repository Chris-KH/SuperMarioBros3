#pragma once
#include <raylib.h>
#include "../lib/bits/stdc++.h"
#include "Global.h"

using namespace std;

class Character;

//Static class to draw GUI using raylib
class GUI {
public:
	static Texture2D heartTexture;
	static Texture2D coinTexture;
	static Texture2D multiplicationSign;
	static Texture2D board;

	static void drawStatusBar(const Character* player);
	static void drawPauseMenu();
	static void drawLevelClear();
	static void drawDeathScreen();
	static void drawGameOverScreen();
	//static void drawButton(const Rectangle& rect);
};