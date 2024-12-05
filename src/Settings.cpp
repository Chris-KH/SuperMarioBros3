#include"../include/Settings.h"

// Constructor to initialize settings with default values
Settings::Settings()
    : screenWidth(1280), screenHeight(800), scale(1), fullscreen(false), sound(true), music(true) {
}

// Getter for screen width
int Settings::getScreenWidth() const {
    return screenWidth;
}

// Setter for screen width
void Settings::setScreenWidth(int width) {
    screenWidth = width;
}

// Getter for screen height
int Settings::getScreenHeight() const {
    return screenHeight;
}

// Setter for screen height
void Settings::setScreenHeight(int height) {
    screenHeight = height;
}

// Getter for scale
int Settings::getScale() const {
    return scale;
}

// Setter for scale
void Settings::setScale(int newScale) {
    scale = newScale;
}

// Getter for fullscreen mode
bool Settings::isFullscreen() const {
    return fullscreen;
}

// Setter for fullscreen mode
void Settings::setFullscreen(bool isFullscreen) {
    fullscreen = isFullscreen;
}

// Getter for sound effects
bool Settings::isSoundEnabled() const {
    return sound;
}

// Setter for sound effects
void Settings::setSound(bool isEnabled) {
    sound = isEnabled;
}

// Getter for music
bool Settings::isMusicEnabled() const {
    return music;
}

// Setter for music
void Settings::setMusic(bool isEnabled) {
    music = isEnabled;
}

// Method to reset settings to default values
void Settings::resetToDefaults() {
    screenWidth = 1280;
    screenHeight = 800;
    scale = 1;
    fullscreen = false;
    sound = true;
    music = true;
}