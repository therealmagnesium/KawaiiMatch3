#include "Game.h"

int main(int argc, char* argv[])
{
    // Allocate on the heap because it's the actual application
    Game* game = new Game(1280, 720, "Kawaii Match!");
    game->Run();
    delete game;

    return 0;
}
