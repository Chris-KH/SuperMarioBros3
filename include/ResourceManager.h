﻿#pragma once
#include <raylib.h>
#include "raylib.h"
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>

using namespace std;
namespace fs = std::filesystem;

class Animation;

template <class T>
class Singleton;

/*
 * ResourceManager class handles the loading and management of game resources,
 * including animations, backgrounds, fonts, music, and sound effects.
 * It provides methods to load resources from a file, retrieve specific resources,
 * bind texture atlases, and play audio tracks.
*/
class ResourceManager {
    template <class T>
    friend class Singleton;
private:
    map<string, unique_ptr<Animation>> animationResource;
    map<string, unique_ptr<Font>> fontResource;
    map<string, unique_ptr<Music>> musicResource;
    map<string, unique_ptr<Sound>> soundResource;

    map<string, Texture2D> textures;
    mutable string currentTrack;
    void loadTextures();
    void loadAnimationFromFile(const string& filePath, const string& fileName);
    void loadAnimation();  // Load animation resources
    void loadFont();      // Load font resources
    void loadMusic();     // Load music resources
    void loadSound();     // Load sound effect resources

    void unloadAnimation();
    void unloadFonts();
    void unloadSounds();
    void unloadMusic();
    void unloadTexture();

    ResourceManager();     // Constructor
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;
public:
    ~ResourceManager();    // Destructor

    void loadAllResource();

    Animation* getAnimation(const string& name) const; 

    const Music* getMusic(const string& name) const;

    const Sound* getSound(const string& name) const;

    Font* getFont(const string& name) const;

    const Texture2D& getTexture(const string& name) const;

    // Play a music track
    void playMusic(const string& trackName) const; 
    bool isMusicPlaying(const string& musicName) const;
    void stopMusic(const string& musicName) const;
    void stopCurrentMusic() const;
    // Play a sound effect
    void playSound(const string& soundName) const; 
    bool isSoundPlaying(const string& soundName) const;
    void stopSound(const string& soundName) const;
};



