#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<memory>
#include<stdlib.h>
#include<time.h>
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

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 600,
    OBJECT_HEIGHT = 50,
    OBJECT_WIDTH = 50,
    INVADER_SPEED = 2,
    GUN_SPEED = 500,
    SHOT_SPEED = 500,
    SHOT_WIDTH = 3,
    SHOT_HEIGHT = 9,
};

bool SDL_IsKeyPressed(SDL_Scancode Code);