#pragma once

#include "Tile.h"
#include "Types.h"
#include <vector>

#define BOARD_ROWS 4
#define BOARD_COLS 5
#define BOARD_TEXTURE_AMOUNT 10

struct Board
{
    Texture2D faceDownTexture;
    Texture2D faces[BOARD_TEXTURE_AMOUNT];
    size_t facesLength = 0;
    Vector2 tileOffset;
    std::vector<Tile*> tiles;
    std::vector<Texture2D> selected;

    void Setup(u32 windowWidth, u32 windowHeight);
    void Fill();
    void Shuffle();
    void Update();
    void Draw();
    void Clean();
};
