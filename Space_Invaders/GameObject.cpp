#include "GameObject.h"
#include "Engine.h"

vec2 GameObject::GetPosition()const
{
    return m_Position;
}

bool GameObject::GetStatus()const
{
    return m_IsAlive;
}

void GameObject::SetPosition(vec2 Position)
{
    m_Position = Position;

    //auto pSpaceInvader = dynamic_cast<SpaceInvader*>(this);
    //if (pSpaceInvader)
    //{
    //    if (pSpaceInvader->m_InvaderID == 0)
    //    {
    //        printf("Invader x=%f , y=%f\n", m_Position.x, m_Position.y);
    //    }
    //}
}

void GameObject::SetStatus(bool Status)
{
    m_IsAlive = Status;
}

void GameObject::DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), Position, Size);
}

void GameObject::DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), srcrect, dstrect);
}
