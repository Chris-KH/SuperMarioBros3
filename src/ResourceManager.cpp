#include"../include/ResourceManager.h"
#include"../include/Animation.h"
#include"../include/Background.h"
#include"../include/Global.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
    unloadAnimation();
    unloadFonts();
    unloadSounds();
    unloadMusic();
}

void ResourceManager::loadAllResource() {
    loadAnimation();
    loadMusic();
    loadSound();
    loadFont();
}

void ResourceManager::loadAnimation() {
    //For character
    string characterFolder = "../assets/Animation/Character/";
    string marioPath1 = characterFolder + "mario1.png";
    Texture2D mario1 = LoadTexture(marioPath1.c_str());

    Animation running = Animation(mario1);
    running.addFrame({ 11, 18, 12, 15 }, { 0, 0 }, 0.3);
    running.addFrame({ 43, 17, 15, 16 }, { 0, 0 }, 0.3);

    animationResource["marioRun"] = make_unique<Animation>(move(running));
}

void ResourceManager::loadFont() {
    string fontFolder = "../assets/Font";

    for (const auto& entry : fs::directory_iterator(fontFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Font font = LoadFont(entry.path().string().c_str());

            if (font.texture.id != 0) {
                fontResource[file] = make_unique<Font>(move(font));
                cout << "Loaded font: " << file << endl;
            }
            else {
                cerr << "Failed to load font: " << entry.path() << endl;
            }
        }
    }
}

void ResourceManager::loadSound() {
    string soundFolder = "../assets/Sound";

    for (const auto& entry : fs::directory_iterator(soundFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Sound sound = LoadSound(entry.path().string().c_str());

            if (sound.stream.buffer != nullptr) {
                soundResource[file] = make_unique<Sound>(move(sound));
            }
            else {
                cerr << "Failed to load sound: " << entry.path() << endl;
            }
        }
    }
}

void ResourceManager::loadMusic() {
    string musicFolder = "../assets/Music";

    for (const auto& entry : fs::directory_iterator(musicFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Music music = LoadMusicStream(entry.path().string().c_str());

            if (music.stream.buffer != nullptr) {
                musicResource[file] = make_unique<Music>(move(music));
            }
            else {
                cerr << "Failed to load music: " << entry.path() << endl;
            }
        }
    }
}

Animation* ResourceManager::getAnimation(const string& name) const {
    return animationResource.at(name).get();
}

const Background* ResourceManager::getBackground(const string& name) const {
    return backgroundResource.at(name).get();
}

const Font* ResourceManager::getFont(const string& name) const {
    return fontResource.at(name).get();
}

const Music* ResourceManager::getMusic(const string& name) const {
    return musicResource.at(name).get();
}

const Sound* ResourceManager::getSound(const string& name) const {
    return soundResource.at(name).get();
}

void ResourceManager::unloadAnimation() {
    animationResource.clear();
}

void ResourceManager::unloadFonts() {
    fontResource.clear(); 
}

void ResourceManager::unloadSounds() {
    soundResource.clear();
}

void ResourceManager::unloadMusic() {
    musicResource.clear();
}

void ResourceManager::playMusic(const string& trackName) const {
    if (SETTINGS.isMusicEnabled() == false) return;

    PlayMusicStream(*getMusic(trackName));
}

void ResourceManager::playSound(const string& soundName) const {
    if (SETTINGS.isSoundEnabled() == false) return;

    PlaySound(*getSound(soundName));
}