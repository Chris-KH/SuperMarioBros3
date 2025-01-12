cmake_minimum_required(VERSION 3.10)

project(CS202-SuperMario)
set(CMAKE_CXX_STANDARD 17)

# Specify the path to raylib
set(RAYLIB_DIR "C:/raylib")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_DIR}/include")
set(RAYLIB_LIB_DIR "${RAYLIB_DIR}/lib")

# Include raylib headers
include_directories(${RAYLIB_INCLUDE_DIR})

# Link to raylib library (static or dynamic)
link_directories(${RAYLIB_LIB_DIR})

# Define source files for your project
set(Main
    src/Animation.cpp
    src/Background.cpp
    src/Camera.cpp
    src/Entity.cpp
    src/FPSManager.cpp
    src/GameEngine.cpp
    src/Global.cpp
    src/GUI.cpp
    src/InputManager.cpp
    src/ResourceManager.cpp
    src/Settings.cpp
    src/Sprite.cpp

    src/BaseBlock.cpp
    src/Brick.cpp
    src/DecorBlock.cpp
    src/Floor.cpp
    src/HiddenBlock.cpp
    src/ItemBlock.cpp
    src/MovingBlock.cpp
    src/PipeBlock.cpp
    src/SolidBlock.cpp
    src/SpikeBlock.cpp
    src/TemporaryBlock.cpp

    src/Item.cpp
    src/ItemFactory.cpp
    src/Coin.cpp
    src/Flower.cpp
    src/Mushroom.cpp
    src/Star.cpp

    src/CharacterState.cpp
    src/NormalState.cpp
    src/FireState.cpp
    src/Fireball.cpp
    src/SuperState.cpp
    src/StarmanState.cpp
    src/FireStarmanState.cpp
    src/SuperStarmanState.cpp

    src/Enemy.cpp
    src/GoomBa.cpp
    src/KoopaTroopa.cpp
    src/Plant.cpp
    src/Shell.cpp

    src/Effect.cpp
    src/TextEffect.cpp

    src/Character.cpp
    src/Mario.cpp
    src/Luigi.cpp

    src/Map.cpp
    src/Menu.cpp
    src/Main.cpp
)

# Add an executable target
add_executable(SuperMario ${Main})

# Link the executable target with raylib and other system libraries
target_link_libraries(SuperMario ${RAYLIB_LIB_DIR}/libraylib.a opengl32 gdi32 kernel32 winmm)
add_custom_command(TARGET SuperMario POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   -E copy_if_different "${RAYLIB_LIB_DIR}/raylib.dll"
                   $<TARGET_FILE_DIR:SuperMario>)