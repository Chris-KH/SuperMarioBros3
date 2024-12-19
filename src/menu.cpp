#include "../include/Menu.h"
#include <memory>
#include <utility>
Menu::Menu() : backgroundTexture({ 0 }) {
    currentState = std::make_unique<MainMenuState>(this);
    audioEnabled = true;
    musicEnabled = true;
    player = nullptr;
    map = nullptr;
    //backgroundTexture = nullptr;
    selectedCharacter = 1;
    selectedMap = 1;
    //// titleScreen = { 0 };

}

Menu::~Menu()
{
    if (backgroundTexture.id != 0) {
        UnloadTexture(backgroundTexture);
        backgroundTexture.id = 0;
    }
}

void Menu::run() {
    InitAudioDevice();
    InitWindow(1280, 800, "Super Mario Bros");
    Texture gameIcon = LoadTexture("../assets/Icon/GameIcon.png");
    Image gameIconImage = LoadImageFromTexture(gameIcon);
    SetWindowIcon(gameIconImage);
    if (backgroundTexture.id == 0)
    {
        backgroundTexture = LoadTexture("../assets/Background/Menuscreen.png");
    }

    RESOURCE_MANAGER.loadAllResource();
    INPUT_MANAGER.bindKey(KEY_A);
    INPUT_MANAGER.bindKey(KEY_D);
    INPUT_MANAGER.bindKey(KEY_S);
    INPUT_MANAGER.bindKey(KEY_R);
    INPUT_MANAGER.bindKey(KEY_SPACE);
    INPUT_MANAGER.bindKey(KEY_LEFT_SHIFT);
    registerBlocks();

    // Tạo một vật thể với texture và InputManager
    Character* player = new Mario(Vector2{ 0,0 });
    RESOURCE_MANAGER.playMusic("World1.mp3");
    this->player = player;
    Map map1;
    map1.loadFromFile("../assets/Map/Map1-1.txt");
    map1.loadBackground("../assets/Map/Map1-1.png");
    Map map2;
    map2.loadFromFile("../assets/Map/Map1-2.txt");
    map2.loadBackground("../assets/Map/map1-2.png");
    Map map3;
    map3.loadFromFile("../assets/Map/Map1-3.txt");
    map3.loadBackground("../assets/Map/map1-3.png");
    loadedMap.push_back(&map1);
    loadedMap.push_back(&map2);
    loadedMap.push_back(&map3);
    this->map = &map1;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(backgroundTexture, {0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height}, {0, 0, 1280, 800}, {0, 0}, 0.0f, WHITE);
        if (SETTINGS.isMusicEnabled())
            UpdateMusicStream(*RESOURCE_MANAGER.getMusic("Overworld.mp3"));       
        if (currentState) {
            currentState->draw();
            currentState->handleInput();
        }
        EndDrawing();
    }
    loadedMap.clear();
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

void Menu::selectMap(int mapIndex) {
    if (mapIndex > 3 || mapIndex <= 0)
        return;
    switch (mapIndex)
    {case 1:
    {     
        this->map = loadedMap[0];
        break;
    }
    case 2:
    {
        this->map = loadedMap[1];
        break;
    }
    case 3:
    {
        this->map = loadedMap[2];
        break;
    }
    default:
        break;
    }
    this->selectedMap = mapIndex;
}

bool Menu::isAudioEnabled() const { return audioEnabled; }

bool Menu::isMusicEnabled() const { return musicEnabled; }

int Menu::getSelectedCharacter() const { return selectedCharacter; }

int Menu::getSelectedMap() const { return selectedMap; }

void Menu::returnToMainMenu() {
    setState(std::make_unique<MainMenuState>(this));
}

MainMenuState::MainMenuState(Menu* menu) { this->menu = menu; }

void MainMenuState::draw() {
    ClearBackground(RAYWHITE);
    
    int titleHeight = 150; // Height of the title area
    int buttonSpacing = 60; // Vertical spacing between buttons
    float buttonStartY = titleHeight + 50; // Position buttons below the title

    // Main Menu Title (just for additional emphasis, optional)
    //DrawText("Main Menu", 500, titleHeight - 80, 40, BLACK);
    // Draw Buttons
    startButton = {440, buttonStartY, 400, 50};
    DrawRectangleRec(startButton, LIGHTGRAY);
    DrawText("Start", 560, buttonStartY + 10, 30, BLACK);

    settingsButton = {440, buttonStartY + buttonSpacing, 400, 50};
    DrawRectangleRec(settingsButton, LIGHTGRAY);
    DrawText("Settings", 540, buttonStartY + buttonSpacing + 10, 30, BLACK);

    charSelectionButton = {440, buttonStartY + buttonSpacing * 2, 400, 50};
    DrawRectangleRec(charSelectionButton, LIGHTGRAY);
    DrawText("Select Character", 500, buttonStartY + buttonSpacing * 2 + 10, 30, BLACK);

    mapSelectionButton = {440, buttonStartY + buttonSpacing * 3, 400, 50};
    DrawRectangleRec(mapSelectionButton, LIGHTGRAY);
    DrawText("Select Map", 530, buttonStartY + buttonSpacing * 3 + 10, 30, BLACK);
}

void MainMenuState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, startButton)) {
            GameEngine game(820.0f, 530.0f, 2779.0f, 512.0f, *menu->map, menu->player);
            game.run();
        } else if (CheckCollisionPointRec(mousePos, settingsButton)) {
            menu->setState(std::make_unique<SettingState>(menu));
        } else if (CheckCollisionPointRec(mousePos, charSelectionButton)) {
            menu->setState(std::make_unique<CharSelection>(menu));
        } else if (CheckCollisionPointRec(mousePos, mapSelectionButton)) {
            menu->setState(std::make_unique<MapSelection>(menu));
        }
    }
}

// SettingState implementation
SettingState::SettingState(Menu* menu) { this->menu = menu; }

void SettingState::draw() {
    ClearBackground(RAYWHITE);

    DrawText("Settings", 300, 100, 40, BLACK);
    DrawText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"), 310, 300, 30, CheckCollisionPointRec(GetMousePosition(), audioButton) ? LIGHTGRAY : BLACK);
    DrawText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"), 310, 350, 30, CheckCollisionPointRec(GetMousePosition(), musicButton) ? LIGHTGRAY : BLACK);
    DrawText("Return to Main Menu", 310, 400, 20, CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);
    
}

void SettingState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, audioButton)) {
            menu->configureSettings(!menu->isAudioEnabled(), menu->isMusicEnabled());
        } else if (CheckCollisionPointRec(mousePos, musicButton)) {
            SETTINGS.setMusic(!menu->isMusicEnabled());
            menu->configureSettings(menu->isAudioEnabled(), !menu->isMusicEnabled());
        } else if (CheckCollisionPointRec(mousePos, backButton)) {
            menu->returnToMainMenu();
        }
    }
}

// CharacterState implementation
CharSelection::CharSelection(Menu* menu) { this->menu = menu; }

void CharSelection::draw() {
    ClearBackground(RAYWHITE);

    DrawText("Character Selection", 300, 100, 40, BLACK);
    DrawText("Mario", 310, 200, 30, CheckCollisionPointRec(GetMousePosition(), marioButton) ? LIGHTGRAY : BLACK);
    DrawText("Luigi", 310, 250, 30, CheckCollisionPointRec(GetMousePosition(), luigiButton) ? LIGHTGRAY : BLACK);
    DrawText("Return to Main Menu", 310, 300, 20, CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);

}

void CharSelection::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, marioButton)) {
            menu->player = new Mario(Vector2{0, 0});
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, luigiButton)) {
            menu->player = new Luigi(Vector2{0, 0});
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, backButton)) {
            menu->returnToMainMenu();
        }
    }
}

// MapState implementation
MapSelection::MapSelection(Menu* menu) { this->menu = menu; }

void MapSelection::draw() {
    ClearBackground(RAYWHITE);

    DrawText("Map Selection", 300, 100, 40, BLACK);
    DrawText("Map1", 310, 210, 30, CheckCollisionPointRec(GetMousePosition(), map1Button) ? LIGHTGRAY : BLACK);
    DrawText("Map2", 310, 260, 30, CheckCollisionPointRec(GetMousePosition(), map2Button) ? LIGHTGRAY : BLACK);
    DrawText("Map3", 310, 310, 30, CheckCollisionPointRec(GetMousePosition(), map3Button) ? LIGHTGRAY : BLACK);
    DrawText("Return to Main Menu", 310, 360, 20, CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);

}

void MapSelection::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, map1Button)) {
            menu->selectMap(1);
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, map2Button)) {
            menu->selectMap(2);
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, map3Button)) {
            menu->selectMap(3);
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, backButton)) {
            menu->returnToMainMenu();
        }
    }
}
