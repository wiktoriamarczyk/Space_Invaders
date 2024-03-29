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
    return rand() % (Max - Min + 1) + Min;
}

float GetRandFloat(float Min, float Max)
{
    float FloatDiff = Max - Min;
    if (FloatDiff <= 1)
        return Min + (FloatDiff)*GetNormalizedFloat();

    const int IntDiff = int(FloatDiff);
    return Min + GetRandInt(0, IntDiff-1) + (1+FloatDiff-IntDiff)* GetNormalizedFloat();
}

float GetNormalizedFloat()
{
    return rand() / float(RAND_MAX);
}

const Color Color::RED(255, 0, 0);
const Color Color::BLUE(0, 0, 255);
const Color Color::WHITE(255, 255, 255);
const Color Color::YELLOW{ 249, 215, 28 };

Color Color::operator*(const Color& other)const
{
    Color Result;
    Result.R = char(((R / 255.0f) * (other.R / 255.0f)) * 255);
    Result.G = char(((G / 255.0f) * (other.G / 255.0f)) * 255);
    Result.B = char(((B / 255.0f) * (other.B / 255.0f)) * 255);
    Result.A = char(((A / 255.0f) * (other.A / 255.0f)) * 255);
    return Result;
}