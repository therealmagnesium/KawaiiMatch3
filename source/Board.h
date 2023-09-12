#pragma once
#include <raylib.h>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 6
#define TILE_SIZE 64
#define TILE_TYPE_AMOUNT 5

enum class TileType
{
    CAT = 0,
    DOG,
    BUNNY,
    PANDA,
    ELEPHANT
};

struct Board
{
    Vector2 offset;
    TileType grid[BOARD_WIDTH * BOARD_HEIGHT];

    void Setup();
    void Draw();
};
