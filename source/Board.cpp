#include "Board.h"

void Board::Setup(u32 windowWidth, u32 windowHeight)
{
    faceDownTexture = LoadTexture("assets/textures/leaf.png");

    tileOffset.x = windowWidth / 2.f - (BOARD_COLS * TILE_SIZE) / 2.f;
    tileOffset.y = windowHeight / 2.f - (BOARD_ROWS * TILE_SIZE) / 2.f;

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            Vector2 position = {j * (TILE_SIZE + 8) + tileOffset.x, i * (TILE_SIZE + 8) + tileOffset.y};
            Tile* tile = new Tile(position);
            tiles.push_back(tile);
        }
    }
}

void Board::Clean()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i])
            delete tiles[i];
    }
}

void Board::Update()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        tiles[i]->tint = {0xFF, 0xFF, 0xFF, 0xFF};

        if (tiles[i]->IsUnderMouse() && !tiles[i]->faceUp)
        {
            tiles[i]->tint = {0xDD, 0xDD, 0xDD, 0xFF};

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                tiles[i]->faceUp = true;
        }
    }
}

void Board::Draw()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i])
            tiles[i]->Draw(faceDownTexture);
    }
}
