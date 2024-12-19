#include "../include/Menu.h"
#include <memory>
#include <utility>
// Menu implementation
Menu::Menu() {
    currentState = std::make_unique<MainMenuState>(this);
    // Default configurations
    player = nullptr;
    map = nullptr;  // Assume a default constructor for the Map class
    selectedCharacter = 1;
    selectedMap = 1;
    //Load background texture in Menu
    titleScreen = LoadTexture("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Background/TitleScreen.png");
}

void Menu::run() {
    InitAudioDevice();
    InitWindow(1280, 800, "Super Mario Bros");
    Texture gameIcon = LoadTexture("C:/Users/Dell/Downloads/CS202-SuperMario/assets/Icon/GameIcon.png");
    Image gameIconImage = LoadImageFromTexture(gameIcon);
    SetWindowIcon(gameIconImage);

    RESOURCE_MANAGER.loadAllResource();
    INPUT_MANAGER.bindKey(KEY_A);
    INPUT_MANAGER.bindKey(KEY_D);
    INPUT_MANAGER.bindKey(KEY_S);
    INPUT_MANAGER.bindKey(KEY_R);
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
    this->map = &map1;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(titleScreen, {0, 0, (float)titleScreen.width, (float)titleScreen.height}, {0, 0, 1280, 800}, {0, 0}, 0.0f, WHITE);
        UpdateMusicStream(*RESOURCE_MANAGER.getMusic("World1.mp3"));
        if (currentState) {
            currentState->draw();
            currentState->handleInput();
        }
        EndDrawing();
    }
    UnloadTexture(titleScreen);
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
    //Set the selected map
    this->selectedMap = mapIndex;
}

void Menu::loadBackground(const std::string &filePath) {
    if (titleScreen.id > 0) {
        UnloadTexture(titleScreen);
    }
    titleScreen = LoadTexture(filePath.c_str());
    if (titleScreen.id == 0) {
        throw std::runtime_error("Failed to load texture!");
    }
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
    float buttonStartY = static_cast<float>(titleHeight + 50);// Position buttons below the title

    DrawText("Main Menu", 500, titleHeight - 80, 40, BLACK);
    // Draw Buttons
    startButton = {440.0f, buttonStartY, 400.0f, 50.0f};
    DrawRectangleRec(startButton, LIGHTGRAY);
    DrawText("Start", 560, static_cast<int>(buttonStartY + 10), 30, BLACK);

    settingsButton = {440.0f, buttonStartY + buttonSpacing, 400.0f, 50.0f};
    DrawRectangleRec(settingsButton, LIGHTGRAY);
    DrawText("Settings", 540, static_cast<int>(buttonStartY + buttonSpacing + 10), 30, BLACK);

    charSelectionButton = {440.0f, buttonStartY + buttonSpacing * 2, 400.0f, 50.0f};
    DrawRectangleRec(charSelectionButton, LIGHTGRAY);
    DrawText("Select Character", 500, static_cast<int>(buttonStartY + buttonSpacing * 2 + 10), 30, BLACK);

    mapSelectionButton = {440.0f, buttonStartY + buttonSpacing * 3, 400.0f, 50.0f};
    DrawRectangleRec(mapSelectionButton, LIGHTGRAY);
    DrawText("Select Map", 530, static_cast<int>(buttonStartY + buttonSpacing * 3 + 10), 30, BLACK);
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
    DrawText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"), 310, 210, 30, CheckCollisionPointRec(GetMousePosition(), audioButton) ? LIGHTGRAY : BLACK);
    DrawText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"), 310, 260, 30, CheckCollisionPointRec(GetMousePosition(), musicButton) ? LIGHTGRAY : BLACK);
    DrawText("Return to Main Menu", 310, 310, 20, CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);

}

void SettingState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, audioButton)) {
            menu->configureSettings(!menu->isAudioEnabled(), menu->isMusicEnabled());
        } else if (CheckCollisionPointRec(mousePos, musicButton)) {
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
    DrawText("Mario", 310, 210, 30, CheckCollisionPointRec(GetMousePosition(), marioButton) ? LIGHTGRAY : BLACK);
    DrawText("Luigi", 310, 260, 30, CheckCollisionPointRec(GetMousePosition(), luigiButton) ? LIGHTGRAY : BLACK);
    DrawText("Return to Main Menu", 310, 310, 20, CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);

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
