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
    SHOT_SPEED = 750,
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

bool SDL_IsKeyPressed(SDL_Scancode Code);