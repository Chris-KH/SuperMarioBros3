cmake_minimum_required(VERSION 3.10)

project(CS202-SuperMario)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR "C:/raylib-5.5")

add_subdirectory(${RAYLIB_DIR} ${CMAKE_BINARY_DIR}/raylib_build)

add_executable(Main
    src/Animation.cpp
    src/Block.cpp
    src/Background.cpp
    src/Character.cpp
    src/Collision.cpp
    src/Enemy.cpp
    src/Entity.cpp
    src/FileHandle.cpp
    src/NormalState.cpp
    src/FireState.cpp
    src/StarmanState.cpp
    src/SuperState.cpp
    src/TailState.cpp
    src/Goomba.cpp
    src/KoopaTroopa.cpp
    src/Plant.cpp
    src/Mushroom.cpp
    src/SuperLeaf.cpp
    src/Item.cpp
    src/Coin.cpp
    src/FPSManager.cpp
    src/GameEngine.cpp
    src/Global.cpp
    src/InputManager.cpp
    src/Luigi.cpp
    src/Mario.cpp
    src/Map.cpp
    src/ResourceManager.cpp
    src/Settings.cpp
    src/Sprite.cpp
    src/menu.cpp
    src/Main.cpp
)

target_link_libraries(Main raylib opengl32 gdi32 kernel32 winmm)

set(CMAKE_SYSTEM_INCLUDE_PATH "C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/ucrt")
set(CMAKE_SYSTEM_LIBRARY_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.20348.0/ucrt/x64")

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
endif()
