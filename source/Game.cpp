#include "Game.h"
#include "Types.h"

#include <raygui.h>
#include <raylib.h>
#include <stdio.h>

#define TARGET_FPS 480
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
    // Initialize Raylib
    InitWindow(data.width, data.height, data.title);
    InitAudioDevice();
    SetTargetFPS(TARGET_FPS);

    // Load the font and gui style
    m_font = LoadFont("assets/ui/font.ttf");
    GuiLoadStyle("assets/ui/lavanda.rgs");

    // Setup the whole board
    m_board.Fill();
    m_board.Shuffle();
    m_board.Setup(data.width, data.height);

    // Setup background shader and audio
    m_bgShader = SetupBackground(data);
    m_pauseShader = SetupPauseShader(data);
    m_playlist.LoadSongs();
    PlayMusicStream(m_playlist.GetCurrentSong());
}

void Game::ShutDown()
{
    // Free allocated memory
    m_board.Clean();
    m_playlist.UnloadSongs();
    UnloadFont(m_font);
    CleanBackground(m_bgShader);
    CleanPauseShader(m_pauseShader);
    CloseAudioDevice();
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

    if (IsKeyPressed(KEY_P))
        m_paused = !m_paused;
}

void Game::Update()
{
    // Handle events and update everything
    HandleEvents();
    HandleAudioChanges(m_playlist.GetCurrentSong(), m_paused);
    UpdateBackground(m_bgShader, &time);
    m_playlist.Update();
    m_board.Update();
}

void Game::Render()
{
    BeginDrawing();
    {
        ClearBackground({0x15, 0x61, 0x84, 0xFF});

        // Apply the background shader only to the background texture
        BeginShaderMode(m_bgShader.shader);
        DrawTexture(m_bgShader.texture, 0, 0, WHITE);
        EndShaderMode();

        m_board.Draw();
        m_playlist.DisplayCurrentSongInfo(m_font);
        DrawFPS(FPS_MARGIN / 2, m_windowData.height - FPS_MARGIN);

        // If the game is paused, enable the pause shader
        if (m_paused)
        {
            BeginShaderMode(m_pauseShader.shader);
            DrawTexture(m_pauseShader.texture, 0, 0, WHITE);
            EndShaderMode();
        }
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
