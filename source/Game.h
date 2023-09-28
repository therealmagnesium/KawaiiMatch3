#pragma once
#include "Background.h"
#include "Board.h"

struct WindowData;

class Game
{
  public:
    Game(const WindowData& data);
    ~Game();

    void Run();

  private:
    void Init(const WindowData& data);
    void ShutDown();

    void ToggleFullscreenWindow();

    void HandleEvents();
    void Update();
    void Render();

  private:
    Board m_board;
    BGShader m_bgShader;
    WindowData m_windowData;
};
