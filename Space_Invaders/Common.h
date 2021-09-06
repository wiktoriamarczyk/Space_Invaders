#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_Mixer.h>
#include<SDL_image.h>

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 600,
};

bool SDL_IsKeyPressed(SDL_Scancode Code);