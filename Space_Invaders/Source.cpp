#include "Common.h"
#include "Game.h"

#ifdef main
// erase SDL2 #define of 'main' keyword
#undef main
#endif

int main()
{
    Game MyGame;

    if (MyGame.Initialize() == false)
    {
        return 1;
    }

    MyGame.Loop();

    return 0;
}