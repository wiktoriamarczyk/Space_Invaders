#include "Game.h"
#include "SpaceInvader.h"
#include "Shield.h"
#include "Gun.h"

Game::~Game()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
    SDL_CloseAudio();
    SDL_DestroyTexture(m_GunIconTexture);
    SDL_DestroyTexture(m_GameOverTexture);
    SpaceInvader::DestroyTextures();
    Shield::DestroyTexture();
}

bool Game::Initialize()
{
    srand(time(NULL));

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

    // stworzenie ikon gry
    SDL_Surface* m_pImage = IMG_Load("../Data/Icon.png");
    m_GunIconTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/GameOver.png");
    m_GameOverTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);

    // stworzenie obiektow gry
    CreateObject();

    // stworzenie czcionki ==TODO==
    m_Font = make_shared<Font>();
    m_Font->LoadFont("../Data/FontData.txt");

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
        
        if (SpaceInvader::ExitGame == true)
        {
            ExitGame();
        }
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

    if (Gun::NumOfLives() <= 0)
    {
        m_GameOver = true;
    }

    if (!m_GameOver)
    {
        if (!m_AllGameObjects.empty())
        {
            for (int i = 0; i < m_AllGameObjects.size();)
            {
                m_AllGameObjects[i]->Update(DeltaTime);

                if (m_AllGameObjects[i]->GetObjectStatus() == false)
                {
                    m_AllGameObjects.erase(m_AllGameObjects.begin() + i);
                }
                else
                {
                    ++i;
                }
            }
        }
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    // render wszystkich obiektow
    if (!m_GameOver)
    {
        if (!m_AllGameObjects.empty())
        {
            for (int i = 0; i < m_AllGameObjects.size(); ++i)
            {
                m_AllGameObjects[i]->Render(m_pRenderer);
            }
        }

        SDL_Rect dstrect = {};
        SDL_Rect srcrect = {};

        switch (Gun::NumOfLives())
        {
        case 3:
            dstrect = { 600, 40, 100, 25 };
            srcrect = { 0, 0, 1500, 300 };
            break;
        case 2:
            dstrect = { 600, 40, 75, 25 };
            srcrect = { 0, 0, 960, 300 };
            break;
        case 1:
            dstrect = { 600, 40, 50, 25 };
            srcrect = { 0, 0, 480, 300 };
            break;
        case 0:
            dstrect = { 0, 0, 0, 0 };
            break;
        }

        SDL_RenderCopy(m_pRenderer, m_GunIconTexture, &srcrect, &dstrect);

        m_Font->DrawText(m_pRenderer, 3, 10, 10, "SCORE:");
        m_Font->DrawText(m_pRenderer, 3, 10, 40, ToString(SpaceInvader::m_NumOfPoints).c_str());
        m_Font->DrawText(m_pRenderer, 3, 250, 10, "HI-SCORE:");
        m_Font->DrawText(m_pRenderer, 3, 600, 10, "LIVES:");

        SDL_RenderPresent(m_pRenderer);
    }
    else
    {
        SDL_Rect dstrect = { 0, 0, 800, 600 };
        SDL_RenderCopy(m_pRenderer, m_GameOverTexture, NULL, &dstrect);
        SDL_RenderPresent(m_pRenderer);
    }
}

void Game::CreateObject()
{
    m_AllGameObjects.clear();

    // inicjalizacja broni
    shared_ptr<Gun> MyGun = make_shared<Gun>();
    MyGun->InitializeGun(m_pRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT - OBJECT_HEIGHT);

    float PosX = 0.0f, PosY = 0.0f;

    // inicjalizacja Space Invaderow
    SpaceInvader::InitializeSpaceInvaderTexture(m_pRenderer);
    // inicjalizacja tarcz
    Shield::InitializeShieldTexture(m_pRenderer);

    for (int ROW = 0; ROW < 4; ++ROW)
    {
        PosX = ROW * 4.2f * OBJECT_WIDTH + OBJECT_WIDTH;
        PosY = SCREEN_HEIGHT - 3 * OBJECT_HEIGHT;
        m_AllGameObjects.push_back(make_shared<Shield>(PosX, PosY, MyGun));
    }

    for (int COLUMN = 0; COLUMN < 5; ++COLUMN)
    {
        for (int ROW = 0; ROW < SCREEN_WIDTH / OBJECT_WIDTH - 3; ++ROW)
        {
            PosX = float(ROW * OBJECT_WIDTH + OBJECT_WIDTH / 2 + ROW * (SCREEN_WIDTH / 100));
            PosY = float(SCREEN_HEIGHT / 6 + COLUMN * OBJECT_HEIGHT);
            m_AllGameObjects.push_back(make_shared<SpaceInvader>(PosX, PosY, MyGun));
        }
    }

    m_AllGameObjects.push_back(move(MyGun));
}

// SCREEN_WIDTH / INVADER_WIDTH - 3: 12 invaderow po 50 pikseli (lacznie zajmuja 600 pikseli)
// ROW * (SCREEN_WIDTH / 100): z odstepami po 8 pikseli miedzy kazdym (lacznie 100 pikseli)
// z 50 pikselowymi przerwami na poczatku i koncu ekranu (100 pikseli)
// 800 pikseli szerokosci ekranu