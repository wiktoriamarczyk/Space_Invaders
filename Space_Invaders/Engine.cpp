#include "Engine.h"
#include "Font.h"
#include "InGameState.h"
#include "MainMenuState.h"
#include "HowToPlayState.h"
#include "VictoryState.h"
#include "SetupState.h"
#include "PlayerData.h"
#include "HighscoreState.h"

Engine* Engine::pSingleton = nullptr;

Engine* Engine::GetSingleton()
{
    return pSingleton;
}

Engine::~Engine()
{
    pSingleton = nullptr;
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    DestroyTextures();
    FreeSounds();
    SDL_Quit();
    SDL_CloseAudio();
}

bool Engine::Initialize()
{
    //srand(time(NULL));

    pSingleton = this;

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
    // sformatowanie audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }
    // utworzenie okna
    m_pWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // stworzenie czcionki
    shared_ptr<Font> MyFont = make_shared<Font>();
    MyFont->LoadFont("../Data/FontData.txt");
    // utworzenie stanu Highscore
    unique_ptr<HighscoreState> MyHighscoreState = make_unique<HighscoreState>(MyFont);
    // stworzenie gracza
    shared_ptr<PlayerData> MyPlayer = make_shared<PlayerData>(*MyHighscoreState);
    // dodanie wszystkich stanow gry do wektora
    m_AllStates.push_back(make_unique<MainMenuState>(MyFont));
    m_AllStates.push_back(make_unique<SetupState>(MyFont, MyPlayer));
    m_AllStates.push_back(make_unique<InGameState>(MyFont, MyPlayer));
    m_AllStates.push_back(make_unique<HowToPlayState>(MyFont));
    m_AllStates.push_back(move(MyHighscoreState));
    m_AllStates.push_back(make_unique<VictoryState>(MyFont, MyPlayer));

    // pierwszym stanem jest Menu gry
    ChangeState(eStateID::MAINMENU);
    // zaladowanie tekstur na watkach
    LoadResources();

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

            if (EVENT.type == SDL_KEYDOWN)
            {
                m_pCurrentState->OnKeyDown(EVENT.key.keysym.scancode);
            }

            if (EVENT.type == SDL_MOUSEBUTTONDOWN)
            {
                m_pCurrentState->OnMouseButtonDown(EVENT.button.button);
            }
        }

        SDL_Delay(1000 / 60);

        m_pCurrentState->Update(1.0f / 60.0f);
        m_pCurrentState->Render(m_pRenderer);

        // domyslnie nastepny stan jest UNKNOWN, gdy nie chcemy przechodzic do nowego stanu, zatem jesli jest tam cos innego, tzn. ze bylo zazadanie zmiany stanu
        if (m_pCurrentState->GetNextStateID() != eStateID::UNKNOWN)
        {
            SDL_Delay(100);
            ChangeState(m_pCurrentState->GetNextStateID());
        }
    }
}

void Engine::ChangeState(eStateID StateID)
{
    for (size_t i = 0; i < m_AllStates.size(); ++i)
    {
        if (m_AllStates[i]->GetStateID() == StateID)
        {
            m_pCurrentState = m_AllStates[i].get();
            m_pCurrentState->OnEnter();
            return;
        }
    }
}

void Engine::ExitGame()
{
    m_IsRunning = false;
}

void Engine::PlaySound(const path& File, float Volume)
{
    for (size_t i = 0; i < m_LoadedSounds.size(); ++i)
    {
        if (m_LoadedSounds[i]->GetName() == File)
        {
            m_LoadedSounds[i]->Play();
            return;
        }
    }
    shared_ptr<Sound> temp_sound = make_shared<Sound>();
    temp_sound->Load(File, Volume);
    m_LoadedSounds.push_back(temp_sound);
    m_LoadedSounds.back()->Play();
}

void Engine::FreeSounds()
{
    for (size_t i = 0; i < m_LoadedSounds.size(); ++i)
    {
        m_LoadedSounds[i]->FreeResources();
    }
}

shared_ptr<Texture> Engine::GetTexture(const path& FileName)const
{
    scoped_lock<mutex> ScopedUnlock(m_EngineMutex);

    for (size_t i = 0; i < m_LoadedTextures.size(); ++i)
    {
        if (m_LoadedTextures[i]->GetName() == FileName)
        {
            return m_LoadedTextures[i];
        }
    }

    return nullptr;
}

void Engine::DisplayTexture(const path& FileName, vec2 Position, DisplayParameters Param )
{
    if (auto pTexture = GetTexture(FileName))
    {
        pTexture->Display(Position, Param);
    }
}

void Engine::DestroyTextures()
{
    scoped_lock<mutex> ScopedUnlock(m_EngineMutex);

    for (size_t i = 0; i < m_LoadedTextures.size(); ++i)
    {
        m_LoadedTextures[i]->FreeResources();
    }
}

vec2i Engine::GetTextureSize(const path& FileName)const
{
    if (auto pTexture = GetTexture(FileName))
    {
        return pTexture->GetSize();
    }
    else return vec2i(0, 0);
}

vec2i Engine::GetMousePos() const
{
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return vec2i(x, y);
}

void Engine::TextureLoadThread()
{
    while (true)
    {
        // blokujemy mutex, by miec wylaczny dostep do wektora z teksturami do zaladowania
        m_EngineMutex.lock();

        // jesli nie ma wiecej tekstur do zaladowania, to odblokuj mutex i zakoncz watek
        if (m_TexturesToLoad.empty())
        {
            m_EngineMutex.unlock();
            return;
        }
        // jesli sa tekstury do zaladowania, to skopiuj ostatnia do lokalnej zmiennej, wyrzuc ja z wektora
        auto text_path = m_TexturesToLoad.back();
        m_TexturesToLoad.erase(m_TexturesToLoad.end() - 1);

        // i odblokuj mutex dla innych watkow, by rowniez sprawdzaly czy sa tekstury do zaladowania
        m_EngineMutex.unlock();

        // stworz teksture
        shared_ptr<Texture> tmp_text = make_shared<Texture>(m_pRenderer);
        // i zaladuj dane
        if (!tmp_text->Load(text_path))
        {
            continue;
        }
        // jak zaladowalismy teksture, to zablokuj mutex, zeby moc wrzucic teksture do listy zaladowanych tekstur
        // aby dwa watki nie chcialy NARAZ w tym samym momencie wpisac tekstury do wektora (crash)
        else
        {
            m_EngineMutex.lock();
            m_LoadedTextures.push_back(tmp_text);
            m_EngineMutex.unlock();
        }
    }
}

void Engine::LoadResources()
{
    m_TexturesToLoad.push_back("SpaceInvader.png");
    m_TexturesToLoad.push_back("SpaceInvaders1.png");
    m_TexturesToLoad.push_back("SpaceInvaders2.png");
    m_TexturesToLoad.push_back("SpaceInvaders3.png");
    m_TexturesToLoad.push_back("SpaceInvaders4.png");
    m_TexturesToLoad.push_back("Boss.png");
    m_TexturesToLoad.push_back("Aureole.png");
    m_TexturesToLoad.push_back("Gun.png");
    m_TexturesToLoad.push_back("Gun_Damaged.png");
    m_TexturesToLoad.push_back("Gun_Shield.png");
    m_TexturesToLoad.push_back("Life_Banner.png");
    m_TexturesToLoad.push_back("Particle3.jpg");
    m_TexturesToLoad.push_back("Particle4.jpg");
    m_TexturesToLoad.push_back("Particle5.png");
    m_TexturesToLoad.push_back("Particle6.png");
    m_TexturesToLoad.push_back("Particle7.png");
    m_TexturesToLoad.push_back("Particle8.png");
    m_TexturesToLoad.push_back("Particle9.png");
    m_TexturesToLoad.push_back("Particle10.png");
    m_TexturesToLoad.push_back("Particle11.png");
    m_TexturesToLoad.push_back("Particle12.png");
    m_TexturesToLoad.push_back("Particle13.png");
    m_TexturesToLoad.push_back("Particle14.png");
    m_TexturesToLoad.push_back("PowerUp_Gun.png");
    m_TexturesToLoad.push_back("PowerUp_Health.png");
    m_TexturesToLoad.push_back("PowerUp_Shield.png");
    m_TexturesToLoad.push_back("Shields.png");
    m_TexturesToLoad.push_back("PowerUp_QuestionMark.png");

    // tworzenie watkow
    for (int i = 0; i < 4; ++i)
    {
        m_LoadingThreads.push_back(thread([this]() { TextureLoadThread(); }));
    }

    // poczekaj, az watki skoncza prace
    for (size_t i = 0; i < m_LoadingThreads.size(); ++i)
    {
        m_LoadingThreads[i].join();
    }

    // funkcje korzystajce z SDL_Renderer nie moga byc zawolane w watku, wiec musimy dokonczyc ladowanie tekstur tutaj (w watku glownym)
    for (size_t i = 0; i < m_LoadedTextures.size(); ++i)
    {
        m_LoadedTextures[i]->PrepareTexture();
    }

}