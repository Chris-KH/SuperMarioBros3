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
        if (entry.is_regular_file()) { // Chỉ xử lý tệp
            string filePath = entry.path().string(); // Đường dẫn đầy đủ
            string fileName = entry.path().stem().string(); // Tên tệp (không có đường dẫn)
            // Kiểm tra định dạng tệp (chỉ lấy PNG và JPG)
            if (filePath.ends_with(".png") || filePath.ends_with(".jpg") || filePath.ends_with(".jpeg")) {
                Texture2D texture = LoadTexture(filePath.c_str());

                // Kiểm tra xem texture có được tải thành công không
                if (texture.id != 0) {
                    textures[fileName] = texture; // Thêm vào map với khóa là tên tệp
                    cout << "Loaded texture: " << fileName << endl;
                }
                else {
                    cerr << "Failed to load texture: " << filePath << endl;
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
        cerr << "Failed to open animation file: " << filePath << endl;
        return;
    }

    string textureName = fileName.substr(0, filePath.length() - 4);
    if (textures.find(textureName) == textures.end()) {
        cerr << "!!!Texture invalid: " << textureName << endl;
        return;
    }

    string line;
    string animationName;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Bỏ qua dòng trống hoặc comment

        if (line[0] == '$') {
            animationName = line.substr(1);
            Animation animation = Animation(getTexture(textureName));
            animationResource[animationName] = make_unique<Animation>(move(animation));
            animationResource[animationName]->setScale(1.f);
        }
        else {
            istringstream iss(line);
            int x, y, width, height;
            float duration;
            if (!(iss >> x >> y >> width >> height >> duration)) {
                cerr << "Invalid frame data in file: " << filePath << endl;
                continue;
            }

            Rectangle source = { (float)x, (float)y, (float)width, (float)height };
            Vector2 offset = { 0.0f, 0.0f }; // Offset mặc định
            animationResource[animationName]->addFrame(source, offset, duration);
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

    PlayMusicStream(*getMusic(trackName));
}

void ResourceManager::playSound(const string& soundName) const {
    if (SETTINGS.isSoundEnabled() == false) return;

    PlaySound(*getSound(soundName));
}