cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project("Match3" VERSION 1.0)

#add_subdirectory("vendor/raylib")

file(GLOB_RECURSE SRC_FILES "source/*.cpp")
add_executable("KawaiiMatch3" "${SRC_FILES}")

#target_include_directories("KawaiiMatch3" PUBLIC "${CMAKE_SOURCE_DIR}/vendor/raylib")

#target_link_directories("KawaiiMatch3" PRIVATE "${CMAKE_SOURCE_DIR}/build/vendor/raylib")
#target_link_libraries("KawaiiMatch3" PRIVATE "raylib")

