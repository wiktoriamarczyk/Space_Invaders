#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<memory>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<optional>
#include<functional>
#include"vec2.h"
#include<SDL.h>
#include<SDL_Mixer.h>
#include<SDL_image.h>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::move;
using std::string;
using std::fstream;
using std::optional;
using std::nullopt;
using std::function;
using std::none_of;

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 600,
    OBJECT_HEIGHT = 50,
    OBJECT_WIDTH = 50,
    BOSS_WIDTH = 200,
    BOSS_HEIGHT = 100,
    INVADER_SPEED = 10,
    GUN_SPEED = 500,
    BOSS_SPEED = 50,
    SHOT_SPEED = 500,
    SHOT_WIDTH = 3,
    SHOT_HEIGHT = 9,
};

enum class eStateID
{
    UNKNOWN,
    MAINMENU,
    INGAME,
    VICTORY, 
    HOWTOPLAY,
};

enum class eTeamID
{
    UNKNOWN,
    PLAYER,
    INVADER,
};

enum class eInvaderDirection
{
    RIGHT,
    LEFT
};

enum class eDrawMode
{
    NORMAL,
    ADDITIVE,
};

struct Color
{
    float R = 1.0f;
    float G = 1.0f;
    float B = 1.0f; 
    float A = 1.0f;

    Color() = default;
    Color(float r, float g, float b, float a = 1.f) : R(r), G(g), B(b), A(a) {}
    Color(int r, int g, int b, int a = 255) : R(r / 255.f), G(g / 255.f), B(b / 255.f), A(a / 255.f) {}
};

struct DisplayParameters
{
    optional<vec2i> DisplaySize;
    eDrawMode DrawMode = eDrawMode::NORMAL;
    vec2 DrawScale = vec2(1.0f, 1.0f);
    vec2 SrcTopLeft = vec2(0, 0);
    vec2 SrcSize = vec2(1, 1);
    Color DrawColor;
};

struct Vec2Rect
{
    vec2 TopLeft;
    vec2 Size;
};

bool SDL_IsKeyPressed(SDL_Scancode Code);

int GetRandInt (int Min, int Max);

float GetRandFloat(float Min, float Max);

float GetNormalizedFloat();