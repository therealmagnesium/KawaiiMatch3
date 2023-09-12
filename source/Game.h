#pragma once
#include "Board.h"
#include "Types.h"

class Game
{
  public:
    Game(u32 width, u32 height, const char* title);
    ~Game();

    void Run();

  private:
    void Init(u32 width, u32 height, const char* title);
    void ShutDown();

    void Update();
    void Render();

  private:
    Board m_board;
};
