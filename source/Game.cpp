#include "Game.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game::Game(u32 width, u32 height, const char* title)
{
    Init(width, height, title);
}

Game::~Game()
{
    ShutDown();
}

void Game::Init(u32 width, u32 height, const char* title)
{
    // Init raylib shit
    InitWindow(width, height, title);
    SetTargetFPS(120);

    srand(time(NULL)); // Generate a random seed

    // Setup game stuff
    m_board.offset.x = width / 2.f - (TILE_SIZE * BOARD_WIDTH) / 2.f;
    m_board.offset.y = height / 2.f - (TILE_SIZE * BOARD_HEIGHT) / 2.f;
    m_board.Setup();
}

void Game::ShutDown()
{
    CloseWindow();
}

void Game::Update()
{
}

void Game::Render()
{

    BeginDrawing();

    ClearBackground(SKYBLUE);
    DrawFPS(10, 10);

    m_board.Draw();

    EndDrawing();
}

void Game::Run()
{
    // Game loop (input, update, render)
    while (!WindowShouldClose())
    {
        Update();
        Render();
    }
}
