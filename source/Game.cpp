#include "Game.h"

#include <raylib.h>
#include <stdio.h>

#define FPS_MARGIN 20

Game::Game(const WindowData& data) : windowData(data)
{
    Init(data);
}

Game::~Game()
{
    ShutDown();
}

void Game::Init(const WindowData& data)
{
    // Init raylib shit
    InitWindow(data.width, data.height, data.title);
    SetTargetFPS(120);

    // Setup game stuff
    board.Fill();
    board.Shuffle();
    board.Setup(data.width, data.height);
}

void Game::ShutDown()
{
    board.Clean();
    CloseWindow();
}

void Game::Update()
{
    board.Update();
}

void Game::Render()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);
    DrawFPS(FPS_MARGIN / 2, windowData.height - FPS_MARGIN);

    board.Draw();

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
