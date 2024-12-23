#include"../include/ResourceManager.h"
#include"../include/Animation.h"
#include"../include/Global.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
    unloadAnimation();
    unloadFonts();
    unloadSounds();
    unloadMusic();
    unloadTexture();
}

void ResourceManager::loadAllResource() {
    loadTextures();
    loadAnimation();
    loadMusic();
    loadSound();
    loadFont();
}

void ResourceManager::loadTextures() {
    string texturesFolder = "../assets/Textures";

    for (const auto& entry : fs::directory_iterator(texturesFolder)) {
        if (entry.is_regular_file()) { 
            string filePath = entry.path().string(); 
            string fileName = entry.path().stem().string(); 

            if (ends_with(filePath, ".png") || ends_with(filePath, ".jpg") || ends_with(filePath, ".jpeg")) {
                Texture2D texture = LoadTexture(filePath.c_str());

                if (texture.id != 0) {
                    textures[fileName] = texture; 
                    cout << "Loaded texture: " << fileName << '\n';
                }
                else {
                    cerr << "Failed to load texture: " << filePath << '\n';
                }
            }
        }
    }
}

void ResourceManager::loadAnimation() {
    string animationFolder = "../assets/Animation";

    for (const auto& entry : fs::directory_iterator(animationFolder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            string filePath = entry.path().string();
            string fileName = entry.path().stem().string();
            loadAnimationFromFile(filePath, fileName);
        }
    }
}

void ResourceManager::loadAnimationFromFile(const string& filePath, const string& fileName) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Failed to open animation file: " << filePath << '\n';
        return;
    }

    string textureName = fileName.substr(0, filePath.length() - 4);
    if (textures.find(textureName) == textures.end()) {
        cerr << "!!!Texture invalid: " << textureName << '\n';
        return;
    }

    string line;
    string animationName;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        if (line[0] == '$') {
            animationName = line.substr(1);
            Animation animation = Animation(getTexture(textureName));
            animationResource[animationName] = make_unique<Animation>(move(animation));
            animationResource[animationName]->setScale(1.f);
        }
        else {
            istringstream iss(line);
            Vector2 offset = { 0.0f, 0.0f }; 
            Vector2 size = { 0.0f, 0.0f };
            int x, y, width, height;
            float duration;
            if (!(iss >> x >> y >> width >> height >> duration >> offset.x >> offset.y >> size.x >> size.y)) {
                cerr << "Invalid frame data in file: " << filePath << '\n';
                continue;
            }

            Rectangle source = { (float)x, (float)y, (float)width, (float)height };
            
            animationResource[animationName]->addFrame(source, offset, size, duration);
        }
    }

    file.close();
}

void ResourceManager::loadFont() {
    string fontFolder = "../assets/Font";

    for (const auto& entry : fs::directory_iterator(fontFolder)) {
        if (entry.is_regular_file()) {
            string file = entry.path().filename().string();
            Font font = LoadFont(entry.path().string().c_str());

            if (font.texture.id != 0) {
                fontResource[file] = make_unique<Font>(move(font));
                cout << "Loaded font: " << file << '\n';
            }
            else {
                cerr << "Failed to load font: " << entry.path() << '\n';
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
                cerr << "Failed to load sound: " << entry.path() << '\n';
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
                cerr << "Failed to load music: " << entry.path() << '\n';
            }
        }
    }
}

Animation* ResourceManager::getAnimation(const string& name) const {
    return animationResource.at(name).get();
}

Font* ResourceManager::getFont(const string& name) const {
    return fontResource.at(name).get();
}

const Music* ResourceManager::getMusic(const string& name) const {
    return musicResource.at(name).get();
}

const Sound* ResourceManager::getSound(const string& name) const {
    return soundResource.at(name).get();
}

const Texture2D& ResourceManager::getTexture(const string& name) const {
    return textures.at(name);
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

void ResourceManager::unloadTexture() {
    for (auto& [name, texture] : textures) {
        UnloadTexture(texture);
    }
    textures.clear();
}

void ResourceManager::playMusic(const string& trackName) const {
    if (SETTINGS.isMusicEnabled() == false) return;
    if (currentTrack == trackName) {
        UpdateMusicStream(*getMusic(trackName));
        return;
    }
    stopCurrentMusic();

    PlayMusicStream(*getMusic(trackName));
    currentTrack = trackName;
}

bool ResourceManager::isMusicPlaying(const string& musicName) const {
    return IsMusicStreamPlaying(*getMusic(musicName));
}

void ResourceManager::stopMusic(const string& musicName) const {
    if (isMusicPlaying(musicName)) StopMusicStream(*getMusic(musicName));
}

void ResourceManager::stopCurrentMusic() const
{
    if (!currentTrack.empty() && isMusicPlaying(currentTrack)) {
        StopMusicStream(*getMusic(currentTrack));
        currentTrack.clear();
    }
}

void ResourceManager::playSound(const string& soundName) const {
    if (SETTINGS.isSoundEnabled() == false) return;

    PlaySound(*getSound(soundName));
}

bool ResourceManager::isSoundPlaying(const string& soundName) const {
    return IsSoundPlaying(*getSound(soundName));
}

void ResourceManager::stopSound(const string& soundName) const {
    if (isSoundPlaying(soundName)) StopSound(*getSound(soundName));
}

