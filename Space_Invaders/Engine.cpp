#include "Engine.h"

Engine* Engine::pSingleton = nullptr;

Engine* Engine::GetSingleton()
{
    return pSingleton;
}

Engine::Engine()
{
    pSingleton = this;
}

Engine::~Engine()
{
    pSingleton = nullptr;
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
    SDL_CloseAudio();
    SDL_DestroyTexture(m_pTexture);
    SDL_FreeSurface(m_pImage);
}

bool Engine::Initialize()
{
    // zainicjalizowanie okna oraz dzwieku
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // zainicjalizowanie obrazkow
    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return 1;
    }

    // utworzenie okna
    SDL_Window* m_pWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // utworzenie renderera
    SDL_Renderer* m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pWindow == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // utworzenie tekstury
    m_pImage = IMG_Load("../Data/SpaceInvader.png");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);

    // stworzenie czcionki ==TODO==

    return true;
}

void Engine::Loop()
{
    while (m_IsRunning)
    {
        SDL_Event EVENT = {};
        while (SDL_PollEvent(&EVENT))
        {
            if (EVENT.type == SDL_QUIT)
                return;
        }

        SDL_Delay(1000 / 60);

        // ->Update(1.0f / 60.0f); ==TODO==
        // ->Render(m_pRenderer);

        // wyswietlanie tekstury
        SDL_Rect dstrect = { 0, 0, 200, 200 };
        SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &dstrect);
        //SDL_RenderCopy(m_pRenderer, texture, NULL, NULL);
        SDL_RenderPresent(m_pRenderer);
    }
}

void Engine::ExitGame()
{
    m_IsRunning = false;
}

// void Engine::PlaySound() {} 
