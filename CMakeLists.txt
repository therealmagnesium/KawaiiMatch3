cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project("KawaiiMemory" VERSION 1.0)

add_subdirectory("vendor/raylib")
add_subdirectory("vendor/raygui")

file(GLOB_RECURSE SRC_FILES "source/*.cpp")
add_executable("KawaiiMemoryGame" "${SRC_FILES}")

target_include_directories("KawaiiMemoryGame" PUBLIC "${CMAKE_SOURCE_DIR}/vendor/raylib/src/" "${CMAKE_SOURCE_DIR}/vendor/raygui/")

target_link_libraries("KawaiiMemoryGame" PRIVATE "raylib" "raygui")

