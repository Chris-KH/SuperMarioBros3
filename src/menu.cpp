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
    RESOURCE_MANAGER.playMusic("Overworld.mp3");
    this->player = player;
    Level level1("../assets/Map/Map1-1.txt", "../assets/Map/Map1-1.png");
    Level level2("../assets/Map/Map1-2.txt", "../assets/Map/map1-2.png");
    Level level3("../assets/Map/Map1-3.txt", "../assets/Map/map1-3.png");

    loadedLevel.push_back(&level1);
    loadedLevel.push_back(&level2);
    loadedLevel.push_back(&level3);
    this->map = &level1;
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
    loadedLevel.clear();
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
        this->map = loadedLevel[0];
        break;
    }
    case 2:
    {
        this->map = loadedLevel[1];
        break;
    }
    case 3:
    {
        this->map = loadedLevel[2];
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

void Menu::setBackground(const std::string& imagePath)
{
    if (backgroundTexture.id != 0) {
        UnloadTexture(backgroundTexture);
    }

    backgroundTexture = LoadTexture(imagePath.c_str());
    if (backgroundTexture.id == 0) {
        throw std::runtime_error("Failed to load background texture: " + imagePath);
    }
}

MainMenuState::MainMenuState(Menu* menu) { 
    this->menu = menu; 
    startButton = { 80, 720, 150, 40 };
    continueButton = { 310, 720, 150, 40 };
    settingsButton = { 540, 720, 150, 40 };
    charSelectionButton = { 770, 720, 200, 40 };
    mapSelectionButton = { 1049, 720, 150, 40 };
}

void MainMenuState::draw() {
    ClearBackground(RAYWHITE);

    // Start Button
    //startButton = { 440, buttonStartY, 400, 50 };
    DrawRectangleRec(startButton, ORANGE);
    DrawText("New Game",
        startButton.x + (startButton.width - MeasureText("New Game", 30)) / 2,
        startButton.y + (startButton.height - 30) / 2,
        30, CheckCollisionPointRec(GetMousePosition(), startButton) ? LIGHTGRAY : BLACK);

    DrawRectangleRec(continueButton, ORANGE);
    DrawText("Continue",
        continueButton.x + (continueButton.width - MeasureText("Continue", 30)) / 2,
        continueButton.y + (continueButton.height - 30) / 2,
        30, CheckCollisionPointRec(GetMousePosition(), continueButton) ? LIGHTGRAY : BLACK);

    // Settings Button
    //settingsButton = { 440, buttonStartY + buttonSpacing, 400, 50 };
    DrawRectangleRec(settingsButton, ORANGE);
    DrawText("Settings",
        settingsButton.x + (settingsButton.width - MeasureText("Settings", 30)) / 2,
        settingsButton.y + (settingsButton.height - 30) / 2,
        30, CheckCollisionPointRec(GetMousePosition(), settingsButton) ? LIGHTGRAY : BLACK);

    // Character Selection Button
    //charSelectionButton = { 440, buttonStartY + buttonSpacing * 2, 400, 50 };
    DrawRectangleRec(charSelectionButton, ORANGE);
    DrawText("Character",
        charSelectionButton.x + (charSelectionButton.width - MeasureText("Character", 30)) / 2,
        charSelectionButton.y + (charSelectionButton.height - 30) / 2,
        30, CheckCollisionPointRec(GetMousePosition(), charSelectionButton) ? LIGHTGRAY : BLACK);

    // Map Selection Button
    //mapSelectionButton = { 440, buttonStartY + buttonSpacing * 3, 400, 50 };
    DrawRectangleRec(mapSelectionButton, ORANGE);
    DrawText("Level",
        mapSelectionButton.x + (mapSelectionButton.width - MeasureText("Level", 30)) / 2,
        mapSelectionButton.y + (mapSelectionButton.height - 30) / 2,
        30, CheckCollisionPointRec(GetMousePosition(), mapSelectionButton) ? LIGHTGRAY : BLACK);
}


void MainMenuState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, continueButton)) {
            GameEngine game(820.0f, 530.0f, *menu->map, menu->player);
            game.run();
        }
        else if (CheckCollisionPointRec(mousePos, startButton)) {
            menu->player->setPosition({ 0,0 });
            menu->player->setVelocity({ 0,0 });
            GameEngine game(820.0f, 512.0f, *menu->map, menu->player);
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

    // Title
    DrawText("Settings", 200, 100, 40, BLACK);

    DrawRectangleRec(audioButton, ORANGE);
    DrawText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"),
        audioButton.x + (audioButton.width - MeasureText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"), 30)) / 2,
        audioButton.y + (audioButton.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), audioButton) ? LIGHTGRAY : BLACK);

    // Music Button
    DrawRectangleRec(musicButton, ORANGE);
    DrawText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"),
        musicButton.x + (musicButton.width - MeasureText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"), 30)) / 2,
        musicButton.y + (musicButton.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), musicButton) ? LIGHTGRAY : BLACK);

    // Back Button
    DrawRectangleRec(backButton, ORANGE);
    DrawText("Return to Main Menu",
        backButton.x + (backButton.width - MeasureText("Return to Main Menu", 20)) / 2,
        backButton.y + (backButton.height - 20) / 2,
        20,
        CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);
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

CharSelection::CharSelection(Menu* menu) { this->menu = menu; }

void CharSelection::draw() {
    ClearBackground(RAYWHITE);

    // Title
    //DrawText("Character Selection", 200, 100, 40, BLACK);

    // Mario Button
    DrawRectangleRec(marioButton, ORANGE);
    DrawText("Mario",
        marioButton.x + (marioButton.width - MeasureText("Mario", 30)) / 2,
        marioButton.y + (marioButton.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), marioButton) ? LIGHTGRAY : BLACK);

    // Luigi Button
    DrawRectangleRec(luigiButton, ORANGE);
    DrawText("Luigi",
        luigiButton.x + (luigiButton.width - MeasureText("Luigi", 30)) / 2,
        luigiButton.y + (luigiButton.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), luigiButton) ? LIGHTGRAY : BLACK);

    // Back Button
    DrawRectangleRec(backButton, ORANGE);
    DrawText("Return to Main Menu",
        backButton.x + (backButton.width - MeasureText("Return to Main Menu", 20)) / 2,
        backButton.y + (backButton.height - 20) / 2,
        20,
        CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);
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

    // Title
    //DrawText("Map Selection", 200, 100, 40, BLACK);

    // Map1 Button
    DrawRectangleRec(map1Button, ORANGE);
    DrawText("Map1",
        map1Button.x + (map1Button.width - MeasureText("Map1", 30)) / 2,
        map1Button.y + (map1Button.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), map1Button) ? LIGHTGRAY : BLACK);

    // Map2 Button
    DrawRectangleRec(map2Button, ORANGE);
    DrawText("Map2",
        map2Button.x + (map2Button.width - MeasureText("Map2", 30)) / 2,
        map2Button.y + (map2Button.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), map2Button) ? LIGHTGRAY : BLACK);

    // Map3 Button
    DrawRectangleRec(map3Button, ORANGE);
    DrawText("Map3",
        map3Button.x + (map3Button.width - MeasureText("Map3", 30)) / 2,
        map3Button.y + (map3Button.height - 30) / 2,
        30,
        CheckCollisionPointRec(GetMousePosition(), map3Button) ? LIGHTGRAY : BLACK);

    // Back Button
    /*DrawRectangleRec(backButton, ORANGE);
    DrawText("Return to Main Menu",
        backButton.x + (backButton.width - MeasureText("Return to Main Menu", 20)) / 2,
        backButton.y + (backButton.height - 20) / 2,
        20,
        CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);*/
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
        }/* else if (CheckCollisionPointRec(mousePos, backButton)) {
            menu->returnToMainMenu();
        }*/
    }
}
