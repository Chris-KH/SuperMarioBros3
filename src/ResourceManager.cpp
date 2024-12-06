#include"../include/ResourceManager.h"

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {
    unloadFonts();
    unloadSounds();
    unloadMusic();
}

void ResourceManager::loadAllResource() {
    loadMusic();
    loadSound();
    loadFont();
}

void ResourceManager::loadSound() {
    string soundFolder = "../assets/Sound";

    for (const auto& entry : fs::directory_iterator(soundFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Sound sound = LoadSound(entry.path().string().c_str());
            if (sound.stream.buffer != nullptr) {
                soundResource[file] = sound;
            }
            else {
                cerr << "Failed to load sound: " << entry.path() << std::endl;
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
                musicResource[file] = music;
            }
            else {
                cerr << "Failed to load music: " << entry.path() << std::endl;
            }
        }
    }
}

void ResourceManager::loadFont() {
    string fontFolder = "../assets/Font";

    for (const auto& entry : fs::directory_iterator(fontFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Font font = LoadFont(entry.path().string().c_str());

            if (font.texture.id != 0) {
                fontResource[file] = font; // Lưu font vào map
                cout << "Loaded font: " << file << endl;
            }
            else {
                cerr << "Failed to load font: " << entry.path() << endl;
            }
        }
    }
}

const Font& ResourceManager::getFont(const string& name) const {
    return fontResource.at(name);
}

const Music& ResourceManager::getMusic(const string& name) const {
    return musicResource.at(name);
}

const Sound& ResourceManager::getSound(const string& name) const {
    return soundResource.at(name);
}


void ResourceManager::unloadFonts() {
    for (auto& [key, font] : fontResource) {
        UnloadFont(font);
    }
    fontResource.clear();
}

void ResourceManager::unloadSounds() {
    for (auto& [key, sound] : soundResource) {
        UnloadSound(sound);
    }
    soundResource.clear();
}

void ResourceManager::unloadMusic() {
    for (auto& [key, music] : musicResource) {
        UnloadMusicStream(music);
    }
    musicResource.clear();
}