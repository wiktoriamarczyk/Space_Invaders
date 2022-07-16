#include "GameObject.h"

vec2 GameObject::GetObjectPosition()
{
    return m_ObjectCenterPosition;
}

bool GameObject::GetObjectStatus()
{
    return m_ObjectIsAlive;
}

void GameObject::SetObjectPosition(vec2 ObjectPos)
{
    m_ObjectCenterPosition = ObjectPos;
}

void GameObject::SetObjectStatus(bool ObjectStatus)
{
    m_ObjectIsAlive = ObjectStatus;
}