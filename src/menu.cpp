#include "../include/Menu.h"
#include "../include/ItemFactory.h"
#include "../include/GUI.h"
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
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN); 
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
    INPUT_MANAGER.bindKey(KEY_W);
    INPUT_MANAGER.bindKey(KEY_SPACE);
    INPUT_MANAGER.bindKey(KEY_LEFT_SHIFT);
    registerBlocks();
    registerItems();
    globalGameEngine = nullptr;
    RESOURCE_MANAGER.playMusic("Overworld.mp3");
    Level level1("../assets/Map/Map1-1.txt", "../assets/Map/Map1-1.png", "World1.mp3","1-1");
    Level level2("../assets/Map/Map1-2.txt", "../assets/Map/map1-2.png", "World4.mp3","1-2");
    Level level3("../assets/Map/Map1-3.txt", "../assets/Map/map1-3.png", "World5.mp3","1-3");
    loadedLevel.push_back(&level1);
    loadedLevel.push_back(&level2);
    loadedLevel.push_back(&level3);

    GUI::heartTexture = LoadTexture("../assets/Background/heart.png");
    GUI::coinTexture = LoadTexture("../assets/Background/coin.png");
    GUI::multiplicationSign = LoadTexture("../assets/Background/multiplicationSign.png");
    GUI::board = LoadTexture("../assets/Background/board.png");

    loadFromConfig("../assets/config.txt");
    selectMap(selectedMap);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(
            backgroundTexture,
            { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height },
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
            { 0, 0 },
            0.0f,
            WHITE
        );
        if (SETTINGS.isMusicEnabled())
            UpdateMusicStream(*RESOURCE_MANAGER.getMusic("Overworld.mp3"));       
        if (currentState) {
            currentState->draw();
            currentState->handleInput();
        }
        EndDrawing();
    }

    saveToConfig("../assets/config.txt");
    loadedLevel.clear();
    if (globalGameEngine != nullptr)
    {
        delete globalGameEngine;
        globalGameEngine = nullptr;
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
    if (globalGameEngine != nullptr)
    {
        delete globalGameEngine;
        globalGameEngine = nullptr;
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
    startButton = { 80, 720, 160, 40 };
    continueButton = { 310, 720, 160, 40 };
    settingsButton = { 540, 720, 160, 40 };
    charSelectionButton = { 770, 720, 200, 40 };
    mapSelectionButton = { 1049, 720, 160, 40 };
}

void MainMenuState::draw() {
    ClearBackground(RAYWHITE);

    //startButton = { 440, buttonStartY, 400, 50 };
    DrawRectangleRec(startButton, ORANGE);
    DrawText("New Game",
        static_cast<int>(startButton.x) + static_cast<int>((startButton.width - MeasureText("New Game", 30)) / 2),
        static_cast<int>(startButton.y + (startButton.height - 30) / 2),
        30, CheckCollisionPointRec(GetMousePosition(), startButton) ? LIGHTGRAY : BLACK);

    DrawRectangleRec(continueButton, ORANGE);
    DrawText("Continue",
        static_cast<int>(continueButton.x) + static_cast<int>((continueButton.width - MeasureText("Continue", 30)) / 2),
        static_cast<int>(continueButton.y + (continueButton.height - 30) / 2),
        30, CheckCollisionPointRec(GetMousePosition(), continueButton) ? LIGHTGRAY : BLACK);

    // Settings Button
    //settingsButton = { 440, buttonStartY + buttonSpacing, 400, 50 };
    DrawRectangleRec(settingsButton, ORANGE);
    DrawText("Settings",
        static_cast<int>(settingsButton.x) + static_cast<int>((settingsButton.width - MeasureText("Settings", 30)) / 2),
        static_cast<int>(settingsButton.y + (settingsButton.height - 30) / 2),
        30, CheckCollisionPointRec(GetMousePosition(), settingsButton) ? LIGHTGRAY : BLACK);

 
    DrawRectangleRec(charSelectionButton, ORANGE);
    DrawText("Character",
        static_cast<int>(charSelectionButton.x) + static_cast<int>((charSelectionButton.width - MeasureText("Charcter", 30)) / 2),
        static_cast<int>(charSelectionButton.y + (charSelectionButton.height - 30) / 2),
        30, CheckCollisionPointRec(GetMousePosition(), charSelectionButton) ? LIGHTGRAY : BLACK);


    DrawRectangleRec(mapSelectionButton, ORANGE);
    DrawText("Level",
        static_cast<int>(mapSelectionButton.x) + static_cast<int>((mapSelectionButton.width - MeasureText("Level", 30)) / 2),
        static_cast<int>(mapSelectionButton.y + (mapSelectionButton.height - 30) / 2),
        30, CheckCollisionPointRec(GetMousePosition(), mapSelectionButton) ? LIGHTGRAY : BLACK);
}


void MainMenuState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, continueButton)) {
            if (globalGameEngine == nullptr)
            {
                menu->player->setPosition({ 16, 400 });
                menu->player->setVelocity({ 0,0 });
                GameEngine* game = new GameEngine(820.0f, 512.0f, *menu->map, menu->player);
                globalGameEngine = game;
            }
            while (globalGameEngine != nullptr) {
                if (globalGameEngine->run())
                {
                    delete globalGameEngine;
                    globalGameEngine = nullptr;
                    if ((menu->getSelectedMap() +1) <= 3)
                    {
                        menu->player->setPosition({ 16, 400 });
                        menu->player->setVelocity({ 0,0 });
                        menu->player->setPhase(Character::DEFAULT_PHASE);
                        menu->selectMap(menu->getSelectedMap() + 1);
                        GameEngine* game = new GameEngine(820.0f, 512.0f, *menu->map, menu->player);
                        globalGameEngine = game;
                    }
                    else break;
                }
                else {
                    if (globalGameEngine->isOver())
                        menu->player->reset();
                    break;
                }
            }
        }
        else if (CheckCollisionPointRec(mousePos, startButton)) {
            if (menu->player)
            {
                menu->player->reset();
            }
            if (globalGameEngine != nullptr)
            {
                delete globalGameEngine;
                globalGameEngine = nullptr;
            }
            GameEngine* game = new GameEngine(820.0f, 512.0f, *menu->map, menu->player);
            globalGameEngine = game;
            while (globalGameEngine != nullptr) {
                if (globalGameEngine->run())
                {
                    delete globalGameEngine;
                    globalGameEngine = nullptr;
                    if ((menu->getSelectedMap() + 1) <= 3)
                    {
                        menu->player->setPosition({ 16,400 });
                        menu->player->setVelocity({ 0,0 });
                        menu->player->setPhase(Character::DEFAULT_PHASE);
                        menu->selectMap(menu->getSelectedMap() + 1);
                        GameEngine* game = new GameEngine(820.0f, 512.0f, *menu->map, menu->player);
                        globalGameEngine = game;
                    }
                    else break;
                }
                else
                {
                    if (globalGameEngine->isOver())
                        menu->player->reset();
                    break;
                }
            }
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
        static_cast<int>(audioButton.x + (audioButton.width - MeasureText(TextFormat("Audio: %s", menu->isAudioEnabled() ? "Enabled" : "Disabled"), 30)) / 2),
        static_cast<int>(audioButton.y + (audioButton.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), audioButton) ? LIGHTGRAY : BLACK);

    // Music Button
    DrawRectangleRec(musicButton, ORANGE);
    DrawText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"),
        static_cast<int>(musicButton.x + (musicButton.width - MeasureText(TextFormat("Music: %s", menu->isMusicEnabled() ? "Enabled" : "Disabled"), 30)) / 2),
            static_cast<int>(musicButton.y + (musicButton.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), musicButton) ? LIGHTGRAY : BLACK);

    // Back Button
    DrawRectangleRec(backButton, ORANGE);
    DrawText("Return to Main Menu",
        static_cast<int>(backButton.x + (backButton.width - MeasureText("Return to Main Menu", 25)) / 2),
            static_cast<int>(backButton.y + (backButton.height - 25) / 2),
        25,
        CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);
}


void SettingState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, audioButton)) {
            SETTINGS.setSound(!menu->isAudioEnabled());
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
        static_cast<int>(marioButton.x + (marioButton.width - MeasureText("Mario", 30)) / 2),
            static_cast<int>(marioButton.y + (marioButton.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), marioButton) ? LIGHTGRAY : BLACK);

    // Luigi Button
    DrawRectangleRec(luigiButton, ORANGE);
    DrawText("Luigi",
        static_cast<int>(luigiButton.x + (luigiButton.width - MeasureText("Luigi", 30)) / 2),
        static_cast<int>(luigiButton.y + (luigiButton.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), luigiButton) ? LIGHTGRAY : BLACK);

    // Back Button
    DrawRectangleRec(backButton, ORANGE);
    DrawText("Return to Main Menu",
        static_cast<int>(backButton.x + (backButton.width - MeasureText("Return to Main Menu", 25)) / 2),
        static_cast<int>(backButton.y + (backButton.height - 25) / 2),
        25,
        CheckCollisionPointRec(GetMousePosition(), backButton) ? LIGHTGRAY : BLACK);
}


void CharSelection::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, marioButton)) {
            delete menu->player;
            menu->player = new Mario(Vector2{16, 400});
            if (globalGameEngine != nullptr)
            {
                delete globalGameEngine;
                globalGameEngine = nullptr;
            }
            menu->returnToMainMenu();
        } 
        else if (CheckCollisionPointRec(mousePos, luigiButton)) 
        {
            delete menu->player;
            menu->player = new Luigi(Vector2{ 16, 400 });
            if (globalGameEngine != nullptr)
            {
                delete globalGameEngine;
                globalGameEngine = nullptr;
            }
            menu->returnToMainMenu();
        } 
        else if (CheckCollisionPointRec(mousePos, backButton)) {
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
        static_cast<int>(map1Button.x + (map1Button.width - MeasureText("Map1", 30)) / 2),
            static_cast<int>(map1Button.y + (map1Button.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), map1Button) ? LIGHTGRAY : BLACK);

    // Map2 Button
    DrawRectangleRec(map2Button, ORANGE);
    DrawText("Map2",
        static_cast<int>(map2Button.x + (map2Button.width - MeasureText("Map2", 30)) / 2),
        static_cast<int>(map2Button.y + (map2Button.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), map2Button) ? LIGHTGRAY : BLACK);

    // Map3 Button
    DrawRectangleRec(map3Button, ORANGE);
    DrawText("Map3",
        static_cast<int>(map3Button.x + (map3Button.width - MeasureText("Map3", 30)) / 2),
        static_cast<int>(map3Button.y + (map3Button.height - 30) / 2),
        30,
        CheckCollisionPointRec(GetMousePosition(), map3Button) ? LIGHTGRAY : BLACK);

}


void MapSelection::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, map1Button)) {
            menu->selectMap(1);
            menu->player->reset();
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, map2Button)) {
            menu->selectMap(2);
            menu->player->reset();
            menu->returnToMainMenu();
        } else if (CheckCollisionPointRec(mousePos, map3Button)) {
            menu->selectMap(3);
            menu->player->reset();
            menu->returnToMainMenu();
        }/* else if (CheckCollisionPointRec(mousePos, backButton)) {
            menu->returnToMainMenu();
        }*/
    }
}

void Menu::saveToConfig(string filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open file for saving: " << filename << endl;
        return;
    }

    outFile << "AudioEnabled: " << (audioEnabled ? "true" : "false") << endl;
    outFile << "MusicEnabled: " << (musicEnabled ? "true" : "false") << endl;
    outFile << "SelectedMap: " << selectedMap << endl;
    if (player) {
        outFile << "CharacterType: " << static_cast<int>(player->getCharacterType()) << endl;
        outFile << "Lives: " << player->getLives() << endl;
        outFile << "Coins: " << player->getCoins() << endl;
        outFile << "Scores: " << player->getScores() << endl;
    }
    else {
        outFile << "CharacterType: -1" << endl; // Placeholder for no character
    }
    outFile.close();
    cout << "Configuration saved to " << filename << endl;
}

void Menu::loadFromConfig(string filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file for loading: " << filename << endl;
        return;
    }

    string key;
    while (inFile >> key) {
        if (key == "AudioEnabled:") {
            string value;
            inFile >> value;
            audioEnabled = (value == "true");
            SETTINGS.setSound((value == "true"));
        }
        else if (key == "MusicEnabled:") {
            string value;
            inFile >> value;
            musicEnabled = (value == "true");
            SETTINGS.setMusic((value == "true"));
        }
        else if (key == "SelectedMap:") {
            inFile >> selectedMap;
        }
        else if (key == "CharacterType:") {
            int type;
            inFile >> type;
            if (type != -1) {
                if (type == 0)
                    this->player = new Mario({ 0, 0 });
                else if (type == 1)
                    this->player = new Luigi({ 0,0 });
            }
        }
        else if (key == "Lives:") {
            int lives;
            inFile >> lives;
            if (player) player->setLives(lives);
        }
        else if (key == "Coins:") {
            int coins;
            inFile >> coins;
            if (player) player->setCoins(coins);
        }
        else if (key == "Scores:") {
            int scores;
            inFile >> scores;
            if (player) player->setScores(scores);
        }
    }

    inFile.close();
    cout << "Configuration loaded from " << filename << endl;
}