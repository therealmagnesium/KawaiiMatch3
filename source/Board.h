#pragma once

#include "Tile.h"
#include "Types.h"
#include <vector>

#define BOARD_ROWS 4
#define BOARD_COLS 5

struct Board
{
    Texture2D faceDownTexture;
    Vector2 tileOffset;
    std::vector<Tile*> tiles;

    void Setup(u32 windowWidth, u32 windowHeight);
    void Update();
    void Draw();
    void Clean();
};
