#include "Common.h"

bool SDL_IsKeyPressed(SDL_Scancode Code)
{
    const Uint8* Keys = SDL_GetKeyboardState(NULL);
    return Keys[Code] != 0;
}

int GetRandInt(int Min, int Max)
{
    if (Min == Max)
    {
        return Max;
    }
    return rand() % (Max - Min) + Min;
}

float GetRandFloat(float Min, float Max)
{
    return GetRandInt((int)Min, (int)Max) + GetNormalizedFloat();
}

float GetNormalizedFloat()
{
    return rand() / float(RAND_MAX);
}