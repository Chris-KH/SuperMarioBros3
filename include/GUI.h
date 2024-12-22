#pragma once
#include <raylib.h>
#include "../lib/bits/stdc++.h"

using namespace std;

class Character;

//Static class to draw GUI using raylib
class GUI {
public:
	static void drawStatusBar(const Character* character);
};