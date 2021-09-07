#include "Game.h"

Game::Game()
{
    // m_Font = Font;
    CreateObject();
}


Game::~Game()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
    SDL_CloseAudio();
   // SDL_DestroyTexture(m_pTexture);
   // SDL_FreeSurface(m_pImage);
}

bool Game::Initialize()
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
    SDL_Window* m_pWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // stworzenie czcionki ==TODO==

    return true;
}

void Game::Loop()
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

        Update(1.0f / 60.0f);
        Render(m_pRenderer);
    }
}

void Game::ExitGame()
{
    m_IsRunning = false;
}

// void Game::PlaySound() {} 


void Game::Update(float Deltatime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        ExitGame();
    }
}

void Game::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    SDL_Surface* pImage = IMG_Load("../Data/SpaceInvader.png");
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pImage);

    SDL_Rect dstrect = { 0, 0, 200, 200 };
    SDL_RenderCopy(pRenderer, pTexture, NULL, &dstrect);
    //SDL_RenderCopy(m_pRenderer, texture, NULL, NULL);
    SDL_RenderPresent(pRenderer);
}

void Game::CreateObject()
{

}
