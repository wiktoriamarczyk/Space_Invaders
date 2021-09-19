#include "MainMenuState.h"
#include "Engine.h"

MainMenuState::MainMenuState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer) : GameState(eStateID::MAINMENU)
{
    m_Font = MyFont;
    m_pRenderer = pRenderer;
    InitializeMainMenuStateTextures();
}

MainMenuState::~MainMenuState()
{
    SDL_DestroyTexture(m_WelcomeInvaderTexture);
}

void MainMenuState::InitializeMainMenuStateTextures()
{
    SDL_Surface* m_pImage = IMG_Load("../Data/SpaceInvader.png");
    m_WelcomeInvaderTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void MainMenuState::OnEnter()
{
    GameState::OnEnter();

    if (m_PlayMusicAgain)
    {
        Engine::GetSingleton()->PlaySound("8-bit_music.wav");
    }
}

void MainMenuState::Update(float DeltaTime) {}

void MainMenuState::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    SDL_Rect dstrect = { 300, 100, 200, 200 };
    SDL_RenderCopy(m_pRenderer, m_WelcomeInvaderTexture, NULL, &dstrect);

    m_Font->DrawText(m_pRenderer, 5, 130, 300, "SPACE INVADERS");

    if (m_Option == 0)
        m_Font->DrawText(m_pRenderer, 3, 270, 400, "->NEW GAME");
    else m_Font->DrawText(m_pRenderer, 3, 270, 400, "  NEW GAME");

    if (m_Option == 1)
        m_Font->DrawText(m_pRenderer, 3, 270, 440, "->HOW TO PLAY");
    else m_Font->DrawText(m_pRenderer, 3, 270, 440, "  HOW TO PLAY");

    if (m_Option == 2)
        m_Font->DrawText(m_pRenderer, 3, 270, 480, "->EXIT");
    else m_Font->DrawText(m_pRenderer, 3, 270, 480, "  EXIT");

    m_Font->DrawText(m_pRenderer, 1, 300, 580, "AUTHOR: WIKTORIA MARCZYK");

    SDL_RenderPresent(m_pRenderer);
}

void MainMenuState::OnKeyDown(SDL_Scancode KeyCode)
{
    // jesli gracz wciska esc, wywolaj zamkniecie programu
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        Engine::GetSingleton()->ExitGame();
    }

    // sprawdzenie czy gracz naciska klawisz w dol, by przejsc do opcji ponizej 
    if (KeyCode == SDL_SCANCODE_DOWN)
    {
        m_Option++;
    }

    // sprawdzenie czy gracz naciska klawisz w gore, by przejsc do opcji powyzej
    else if (KeyCode == SDL_SCANCODE_UP)
    {
        m_Option--;
    }

    // po nacisieciu enter dostajemy sie do okna gry lub wychodzimy z gry
    else if (KeyCode == SDL_SCANCODE_RETURN)
    {
        if (m_Option == 0)
        {
            m_PlayMusicAgain = true;
            Mix_HaltChannel(-1);
            m_NextStateID = eStateID::INGAME;
        }
        if (m_Option == 1)
        {
            m_PlayMusicAgain = false;
            m_NextStateID = eStateID::HOWTOPLAY;
        }
        if (m_Option == 2)
        {
            Engine::GetSingleton()->ExitGame();
        }
    }
}
