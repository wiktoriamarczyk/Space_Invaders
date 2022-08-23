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
#include<regex>
#include<filesystem>
#include<mutex>
#include<thread>
#include<chrono>
#include<sstream>

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
using std::dynamic_pointer_cast;
using std::regex;
using std::regex_match;
using std::filesystem::path;
using std::mutex;
using std::thread;
using std::scoped_lock;
using std::ofstream;
using std::getline;
using std::pair;

const path DataPath = "../Data";

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 800,
   //WINDOW_WIDTH = 1520,
   //WINDOW_HEIGHT = 900,
    OBJECT_HEIGHT = 50,
    OBJECT_WIDTH = 50,
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
    HIGHSCORE,
    SETUP,
};

enum class eTeamID
{
    UNKNOWN,
    PLAYER,
    INVADER,
    SUICIDE,
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

enum class ePowerUpType
{
    UNKNOWN = 0,
    GUN_IMPROVMENT,
    HEALTH,
    SHIELD,
    ANGRY_INVADER,
};

enum class eParticleMode
{
    POINT_EXPLOSION,
    STARS_BACKGROUND
};

struct Color
{
    unsigned char R = 255;
    unsigned char G = 255;
    unsigned char B = 255;
    unsigned char A = 255;

    Color() = default;
    //Color(float r, float g, float b, float a = 1.f) : R(r), G(g), B(b), A(a) {}
    Color(int r, int g, int b, int a = 255) : R(r), G(g), B(b), A(a) {}

    static const Color RED;
    static const Color BLUE;
    static const Color WHITE;
    static const Color YELLOW;

    Color operator*(const Color& other)const;
};

struct DisplayParameters
{
    optional<vec2i> DisplaySize;
    eDrawMode DrawMode = eDrawMode::NORMAL;
    vec2 DrawScale = vec2(1.0f, 1.0f);
    vec2 SrcTopLeft = vec2(0, 0);
    vec2 SrcSize = vec2(1, 1);
    vec2 Pivot = vec2(0, 0);
    Color DrawColor;
    float Rotation = 0.0f;
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