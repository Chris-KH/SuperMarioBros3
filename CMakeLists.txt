cmake_minimum_required(VERSION 3.10)

project(CS202-SuperMario)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR "C:/raylib-5.5")

include_directories(${RAYLIB_DIR}/src)
link_directories(${RAYLIB_DIR}/src)

add_executable(Menu
    src/Animation.cpp
    src/Block.cpp
    src/Background.cpp
    src/Character.cpp
    src/Collision.cpp
    src/Enemy.cpp
    src/Entity.cpp
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
)

target_link_libraries(Menu raylib opengl32 gdi32 kernel32 winmm)

set(CMAKE_SYSTEM_INCLUDE_PATH "C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/ucrt")
set(CMAKE_SYSTEM_LIBRARY_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.20348.0/ucrt/x64")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
endif()
