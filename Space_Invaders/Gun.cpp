#include "Gun.h"
#include "Engine.h"

Gun::Gun()
{
    m_Speed = 500;
}

void Gun::Update(float DeltaTime)
{
    // update strzal i usuwanie tych, ktore zostaly juz wystrzelone
    for (int i = 0; i < m_Shots.size();)
    {
        m_Shots[i]->Update(DeltaTime);

        if (m_Shots[i]->GetStatus() == false)
        {
            m_Shots.erase(m_Shots.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void Gun::Render(SDL_Renderer* pRenderer)
{
   for (int i = 0; i < m_Shots.size(); ++i)
   {
       m_Shots[i]->Render(pRenderer);
   }
}

vector<shared_ptr<Shot>>& Gun::GetShots()
{
    return m_Shots;
}

void Gun::Shoot(vec2 Pos, vec2i Size, int Speed, eTeamID Team)
{
    m_Shots.push_back(make_shared<Shot>(Pos, Size, Speed, Team));
}