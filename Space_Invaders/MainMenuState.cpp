#include "MainMenuState.h"
#include "Engine.h"

MainMenuState::MainMenuState(shared_ptr<Font> MyFont) : GameState(eStateID::MAINMENU)
{
    m_Font = MyFont;
}

void MainMenuState::OnEnter()
{
    m_GameOver = false;

    GameState::OnEnter();

    m_Option = 0;

    if (m_PlayMusicAgain)
    {
        Engine::GetSingleton()->PlaySound("8-bit_music.wav");
    }
}

void MainMenuState::Update(float DeltaTime) {}

void MainMenuState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    DisplayTexture("SpaceInvader.png", vec2(300, 140), DisplayParameters{.DisplaySize = vec2i(200, 200)});

    m_ColorTimer--;
    if (m_ColorTimer <= 0)
    {
        m_TxtColor = { GetRandFloat(1.f, 255.f), GetRandFloat(1.f, 255.f), GetRandFloat(1.f, 255.f) };
        m_ColorTimer = 10.f;
    }

    m_Font->DrawText(pRenderer, 5, 130, SCREEN_HEIGHT / 2 - 40, "SPACE INVADERS", m_TxtColor);

    if (m_Option == 0)
        m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 40, "->NEW GAME");
    else m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 40, "  NEW GAME");

    if (m_Option == 1)
        m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 80, "->HOW TO PLAY");
    else m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 80, "  HOW TO PLAY");

    if (m_Option == 2)
        m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 120, "->HIGHSCORE");
    else m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 120, "  HIGHSCORE");

    if (m_Option == 3)
        m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 160, "->EXIT");
    else m_Font->DrawText(pRenderer, 3, 270, SCREEN_HEIGHT / 2 + 160, "  EXIT");

    m_Font->DrawText(pRenderer, 1, SCREEN_WIDTH/2 - SCREEN_WIDTH/10, SCREEN_HEIGHT - 150, "AUTHOR: WIKTORIA MARCZYK");

    SDL_RenderPresent(pRenderer);
}

void MainMenuState::OnKeyDown(SDL_Scancode KeyCode)
{
    // jesli gracz wciska esc, wywolaj zamkniecie programu
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        Engine::GetSingleton()->ExitGame();
    }

    // sprawdzenie czy gracz naciska klawisz w dol, by przejsc do opcji ponizej 
    if (KeyCode == SDL_SCANCODE_DOWN && m_Option < 3)
    {
        m_Option++;
    }

    // sprawdzenie czy gracz naciska klawisz w gore, by przejsc do opcji powyzej
    else if (KeyCode == SDL_SCANCODE_UP && m_Option > 0)
    {
        m_Option--;
    }

    // po nacisieciu enter dostajemy sie do danego okna gry lub wychodzimy z gry
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
            m_PlayMusicAgain = false;
            m_NextStateID = eStateID::HIGHSCORE;
        }
        if (m_Option == 3)
        {
            Engine::GetSingleton()->ExitGame();
        }
    }
}