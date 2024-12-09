cmake_minimum_required(VERSION 3.10)

//project(CS202-SuperMario)

set(CMAKE_CXX_STANDARD 11)

set(RAYLIB_DIR "C:/Users/Dell/Downloads/CS202-SuperMario/lib")

include_directories(${RAYLIB_DIR}/include)

link_directories(${RAYLIB_DIR}/lib)

set(SOURCES
    src/main.cpp

)

add_executable(SuperMario src/Main.cpp)

target_link_libraries(SuperMario raylib)
target_link_libraries(SuperMario raylib opengl32 gdi32)

