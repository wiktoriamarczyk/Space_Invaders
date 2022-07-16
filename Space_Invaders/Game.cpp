#include "Game.h"
#include "SpaceInvader.h"

Game::~Game()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
    SDL_CloseAudio();
}

bool Game::Initialize()
{
    // zainicjalizowanie okna oraz dzwieku
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // zainicjalizowanie obrazkow
    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }

    // utworzenie okna
    m_pWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // utworzenie renderera
     m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pWindow == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // stworzenie obiektow gry
    CreateObject();

    // stworzenie czcionki ==TODO==
    // m_Font = Font;

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
        Render();
    }
}

void Game::ExitGame()
{
    m_IsRunning = false;
}

// void Game::PlaySound() {} 

void Game::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        ExitGame();
    }

    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {
        if (m_AllGameObjects[i]->GetObjectStatus())
        {
            m_AllGameObjects[i]->Update(DeltaTime);
        }
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    // render wszystkich obiektow
    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {
        if (m_AllGameObjects[i]->GetObjectStatus())
        {
            m_AllGameObjects[i]->Render(m_pRenderer);
        }
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::CreateObject()
{
    m_AllGameObjects.clear();

    // inicjalizacja Space Invaderow
    float PosX = 0.0f, PosY = 0.0f;
    // SCREEN_WIDTH / INVADER_WIDTH - 3: 12 invaderow po 50 pikseli (lacznie zajmuja 600 pikseli)
    // ROW * (SCREEN_WIDTH / 100): z odstepami po 8 pikseli miedzy kazdym (lacznie 100 pikseli)
    // z 50 pikselowymi przerwami na poczatku i koncu ekranu (100 pikseli)
    // 800 pikseli szerokosci ekranu rozdysponowane

    SpaceInvader::LoadTexture();

    for (int COLUMN = 0; COLUMN < 5; ++COLUMN)
    {
        for (int ROW = 0; ROW < SCREEN_WIDTH / INVADER_WIDTH - 3; ++ROW)
        {
            PosX = ROW * INVADER_WIDTH + INVADER_WIDTH / 2 + ROW * (SCREEN_WIDTH / 100);
            PosY = SCREEN_HEIGHT / 6 + COLUMN * INVADER_HEIGHT;
            m_AllGameObjects.push_back(make_shared<SpaceInvader>(m_pRenderer, PosX, PosY));
        }
    }
}
