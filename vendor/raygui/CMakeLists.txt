project("raygui")
add_library("raygui" "raygui.c")

target_include_directories("raygui" PUBLIC "${CMAKE_SOURCE_DIR}/vendor/raylib/src/")

