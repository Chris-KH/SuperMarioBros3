#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "../lib/raylib.h"
class GameCamera {
private:
	float cameraX;
	float cameraY;
	float cameraWidth;
	float cameraHeight;
	float scale; // Scaling factor
	RenderTexture2D renderTexture;
public:
	GameCamera(float width, float height, float initialScale = 1.0f);
	~GameCamera();
	void loadRenderTexture(Vector2 size);
	void update(float characterX, float characterY);
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
};
class special
{};

#endif // !CAMERA_H