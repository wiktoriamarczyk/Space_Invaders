#pragma once
#include "Common.h"
#include "vec2.h"

class GameObject
{
public:
    virtual void Update(float DeltaTime) = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual bool OnMouseButtonDown(int Button) { return false; };
    virtual bool IsCursorOnButton()const { return false; };
    vec2 GetPosition()const;
    bool GetStatus()const;
    void SetPosition(vec2 Position);
    void SetStatus(bool Status);
    void SetColor(Color color);
    void DisplayTexture(const string& FileName, vec2 Position, DisplayParameters Param = {});

protected:
    vec2  m_Position;
    vec2i m_Size;
    bool  m_IsAlive = true;
    Color m_Color;
};