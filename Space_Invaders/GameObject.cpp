#include "GameObject.h"
#include "Engine.h"

vec2 GameObject::GetPosition()const
{
    return m_Position;
}

vec2i GameObject::GetSize() const
{
    return m_Size;
}

bool GameObject::GetStatus()const
{
    return m_IsAlive;
}

void GameObject::SetPosition(vec2 Position)
{
    m_Position = Position;
}

void GameObject::SetStatus(bool Status)
{
    m_IsAlive = Status;
}

void GameObject::SetColor(Color color)
{
    m_Color = color;
}

void GameObject::SetSpeed(int Value)
{
    m_Speed = Value;
}

int GameObject::GetSpeed()
{
    return m_Speed;
}

void GameObject::DisplayTexture(const string& FileName, vec2 Position, DisplayParameters Param)
{
    Engine::GetSingleton()->DisplayTexture((FileName).c_str(), Position, Param);
}