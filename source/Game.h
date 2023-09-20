#pragma once
#include "Board.h"
#include "Types.h"

struct WindowData
{
    u32 width;
    u32 height;
    const char* title;
};

class Game
{
  public:
    Game(const WindowData& data);
    ~Game();

    void Run();

  private:
    void Init(const WindowData& data);
    void ShutDown();

    void Update();
    void Render();

  private:
    Board board;
    WindowData windowData;
};
