#pragma once
#include <raylib.h>
#include "raylib.h"
#include <map>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

class Animation;
class Background;

/*
 * ResourceManager class handles the loading and management of game resources,
 * including animations, backgrounds, fonts, music, and sound effects.
 * It provides methods to load resources from a file, retrieve specific resources,
 * bind texture atlases, and play audio tracks.
*/
class ResourceManager {
private:
 /*   map<string, Animation> animationResource;
    map<string, Background> backgroundResource;*/
    map<string, Font> fontResource;
    map<string, Music> musicResource;
    map<string, Sound> soundResource;

    void loadAnimation();  // Load animation resources
    void loadBackground(); // Load background resources
    void loadFont();      // Load font resources
    void loadMusic();     // Load music resources
    void loadSound();     // Load sound effect resources

    void unloadFonts();
    void unloadSounds();
    void unloadMusic();

public:
    ResourceManager();     // Constructor
    ~ResourceManager();    // Destructor

    void loadAllResource();

    // Retrieve an Animation resource
    const Animation& getAnimation(const string& name) const; 

    // Retrieve a Background resource
    const Background& getBackground(const string& name) const; 

    const Music& getMusic(const string& name) const;

    const Sound& getSound(const string& name) const;

    const Font& getFont(const string& name) const;

    // Play a music track
    void playMusic(const string& trackName, bool loop) const; 

    // Play a sound effect
    void playSound(const string& soundName) const; 
};



