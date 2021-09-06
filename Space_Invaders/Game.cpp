#include "Game.h"

Game::Game()
{
    // m_Font = Font;
    CreateObject();
}

void Game::Update(float Deltatime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        Engine::GetSingleton()->ExitGame();
    }
}

void Game::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);


}

void Game::CreateObject()
{

}
