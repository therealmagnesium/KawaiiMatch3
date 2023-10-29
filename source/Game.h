#pragma onceme
#include "Audio.h"
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
    bool m_paused = false;
    Board m_board;
    BGShader m_bgShader;
    PauseShader m_pauseShader;
    Font m_font;
    Playlist m_playlist;
    WindowData m_windowData;
};
