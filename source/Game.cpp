#include "Game.h"
#include "Types.h"

#include <raygui.h>
#include <raylib.h>
#include <stdio.h>

#define FPS_MARGIN 20

static float time = 0.f;

Game::Game(const WindowData& data) : m_windowData(data)
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
    SetTargetFPS(480);
    GuiLoadStyle("assets/ui/lavanda.rgs");

    m_bgShader = SetupBackground(data);

    // Setup game stuff
    m_board.Fill();
    m_board.Shuffle();
    m_board.Setup(data.width, data.height);
}

void Game::ShutDown()
{
    // Free allocated memory
    m_board.Clean();
    CleanBackground(m_bgShader);
    CloseWindow();
}

void Game::ToggleFullscreenWindow()
{
    if (!IsWindowFullscreen())
    {
        // Set the window size to the monitor's size, then toggle fullscreen
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else
    {
        // Toggle fullscreen, then set the window size to m_windowData
        ToggleFullscreen();
        SetWindowSize(m_windowData.width, m_windowData.height);
    }
}

void Game::HandleEvents()
{
    time = GetTime();

    // Handle closing the game
    if (IsKeyPressed(KEY_ESCAPE))
        ShutDown();

    // Check for when the user wants to go fullscreen
    if (IsKeyPressed(KEY_F))
        ToggleFullscreenWindow();
}

void Game::Update()
{
    // Handle events and update everything
    HandleEvents();
    UpdateBackground(m_bgShader, &time);
    m_board.Update();
}

void Game::Render()
{
    BeginDrawing();
    {
        ClearBackground({0x15, 0x61, 0x84, 0xFF});

        // Apply the background shader only to the background texture
        BeginShaderMode(m_bgShader.shader);
        {
            DrawTexture(m_bgShader.texture, 0, 0, WHITE);
        }
        EndShaderMode();

        m_board.Draw();
        DrawFPS(FPS_MARGIN / 2, m_windowData.height - FPS_MARGIN);
    }
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
