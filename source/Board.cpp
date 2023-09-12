#include "Board.h"
#include "raylib.h"
#include <stdlib.h>
void Board::Setup()
{
    // Loop through the board and fill it with random tiles
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            TileType tile = (TileType)(rand() % TILE_TYPE_AMOUNT);
            grid[i * BOARD_WIDTH + j] = tile;
        }
    }
}

void Board::Draw()
{
    // Loop through the board, draw the grid and tiles
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            Rectangle cellRect = {(float)j * TILE_SIZE + offset.x, (float)i * TILE_SIZE + offset.y, TILE_SIZE,
                                  TILE_SIZE};
            DrawRectangleLinesEx(cellRect, 2.f, PINK);

            TileType tile = grid[i * BOARD_WIDTH + j];
            switch (tile)
            {
            case TileType::CAT:
                DrawCircleV({cellRect.x + (cellRect.width / 2.f), cellRect.y + (cellRect.width / 2.f)}, 25.f, YELLOW);
                break;
            case TileType::DOG:
                DrawCircleV({cellRect.x + (cellRect.width / 2.f), cellRect.y + (cellRect.width / 2.f)}, 25.f, BEIGE);
                break;
            case TileType::BUNNY:
                DrawCircleV({cellRect.x + (cellRect.width / 2.f), cellRect.y + (cellRect.width / 2.f)}, 25.f, WHITE);
                break;
            case TileType::PANDA:
                DrawCircleV({cellRect.x + (cellRect.width / 2.f), cellRect.y + (cellRect.width / 2.f)}, 25.f, BLACK);
                break;
            case TileType::ELEPHANT:
                DrawCircleV({cellRect.x + (cellRect.width / 2.f), cellRect.y + (cellRect.width / 2.f)}, 25.f, GRAY);
                break;
            }
        }
    }
}
