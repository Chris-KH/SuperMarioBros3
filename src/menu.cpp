#include "../include/Menu.h"
#include <memory>
#include <utility>
// Menu implementation
Menu::Menu() {
    currentState = std::make_unique<MainMenuState>(this);

    // Default configurations
    player = nullptr;
    map = nullptr;  // Assume a default constructor for the Map class
}

void Menu::run() {
    InitAudioDevice();
    InitWindow(1280, 800, "Super Mario Bros");

    RESOURCE_MANAGER.loadAllResource();
    INPUT_MANAGER.bindKey(KEY_A);
    INPUT_MANAGER.bindKey(KEY_D);
    INPUT_MANAGER.bindKey(KEY_S);
    INPUT_MANAGER.bindKey(KEY_SPACE);
    INPUT_MANAGER.bindKey(KEY_LEFT_SHIFT);
    registerBlocks();
    Texture2D texture = LoadTexture("../SuperMario/images.png");

    // Tạo một vật thể với texture và InputManager
    Character* player = new Mario(Vector2{ 0,0 });
    RESOURCE_MANAGER.playMusic("World1.mp3");
    this->player = player;
    Map map1;
    map1.loadFromFile("../assets/Map/Map1-1.txt");
    map1.loadBackground("../assets/Map/Map1-1.png");
    this->map = map;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (currentState) {
            currentState->draw();
            currentState->handleInput();
        }

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}


void Menu::setState(std::unique_ptr<MenuState> newState) {
    currentState = std::move(newState);
}

void Menu::configureSettings(bool audioEnabled, bool musicEnabled) {
    // Update settings (these should ideally update private member variables)
    this->audioEnabled = audioEnabled;
    this->musicEnabled = musicEnabled;
}

void Menu::selectCharacter(int characterIndex) {
    // Set the player's character
    this->selectedCharacter = characterIndex;
}

//void Menu::selectMap(int mapIndex) {
//    // Set the selected map
//    this->selectedMap = mapIndex;
//}

bool Menu::isAudioEnabled() const {
    return audioEnabled;
}

bool Menu::isMusicEnabled() const {
    return musicEnabled;
}

int Menu::getSelectedCharacter() const {
    return selectedCharacter;
}

int Menu::getSelectedMap() const {
    return selectedMap;
}

void Menu::returnToMainMenu()
{
    setState(std::make_unique<MainMenuState>(this));
}

MainMenuState::MainMenuState(Menu* menu) {
    this->menu = menu;
}

void MainMenuState::draw() {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("Main Menu", 300, 100, 40, BLACK);
    DrawText("Start", 300, 200, 40, BLACK);
    DrawText("Settings", 300, 250, 30, BLACK);
    DrawText("Select Character", 300, 300, 30, BLACK);
    DrawText("Select Map", 300, 350, 30, BLACK);
    DrawText("Exit", 300, 400, 30, BLACK);

    EndDrawing();
}

void MainMenuState::handleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        GameEngine game((float)820, (float)530, (float)2779, (float)512, *menu->map, menu->player);
        game.run();
    }
    if (IsKeyPressed(KEY_TWO)) {
        menu->setState(std::make_unique<SettingState>(menu));
    }
    else if (IsKeyPressed(KEY_THREE)) {
        menu->setState(std::make_unique<CharSelection>(menu));
    }
    else if (IsKeyPressed(KEY_FOUR)) {
        menu->setState(std::make_unique<MapSelection>(menu));
    }
    else if (IsKeyPressed(KEY_FIVE)) {
        CloseWindow(); 
    }
}

// SettingState implementation
SettingState::SettingState(Menu* menu) {
    this->menu = menu;
}

void SettingState::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Settings", 300, 100, 40, BLACK);
    DrawText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"), 300, 200, 30, BLACK);
    DrawText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"), 300, 250, 30, BLACK);
    DrawText("Press 1 to Toggle Audio", 300, 300, 20, DARKGRAY);
    DrawText("Press 2 to Toggle Music", 300, 330, 20, DARKGRAY);
    DrawText("Press 3 to Return to Main Menu", 300, 360, 20, DARKGRAY);

    EndDrawing();
}

void SettingState::handleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        menu->configureSettings(!menu->isAudioEnabled(), menu->isMusicEnabled());
    }
    else if (IsKeyPressed(KEY_TWO)) {
        menu->configureSettings(menu->isAudioEnabled(), !menu->isMusicEnabled());
    }
    else if (IsKeyPressed(KEY_THREE)) {
        menu->returnToMainMenu();
    }
}

// CharacterState implementation
CharSelection::CharSelection(Menu* menu) {
    this->menu = menu;
}

void CharSelection::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Character Selection", 300, 100, 40, BLACK);
    DrawText("1. Warrior", 300, 200, 30, BLACK);
    DrawText("2. Mage", 300, 250, 30, BLACK);
    DrawText("3. Archer", 300, 300, 30, BLACK);
    DrawText(TextFormat("Current Selection: %d", menu->getSelectedCharacter()), 300, 350, 30, DARKGRAY);

    EndDrawing();
}

void CharSelection::handleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        //menu->selectCharacter(1);
        menu->returnToMainMenu();
    }
    else if (IsKeyPressed(KEY_TWO)) {
        //menu->selectCharacter(2);
        menu->returnToMainMenu();
    }
    else if (IsKeyPressed(KEY_THREE)) {
        //menu->selectCharacter(3);
        menu->returnToMainMenu();
    }
}

// MapState implementation
MapSelection::MapSelection(Menu* menu) {
    this->menu = menu;
}

void MapSelection::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Map Selection", 300, 100, 40, BLACK);
    DrawText("1. Forest", 300, 200, 30, BLACK);
    DrawText("2. Desert", 300, 250, 30, BLACK);
    DrawText("3. Castle", 300, 300, 30, BLACK);
    DrawText(TextFormat("Current Selection: %d", menu->getSelectedMap()), 300, 350, 30, DARKGRAY);

    EndDrawing();
}

void MapSelection::handleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        //menu->selectMap(1);
        menu->returnToMainMenu();
    }
    else if (IsKeyPressed(KEY_TWO)) {
        //menu->selectMap(2);
        menu->returnToMainMenu();
    }
    else if (IsKeyPressed(KEY_THREE)) {
        //menu->selectMap(3);
        menu->returnToMainMenu();
    }
}
