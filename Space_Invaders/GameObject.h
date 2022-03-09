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
    vec2i GetPosition()const;
    bool GetStatus()const;
    void SetPosition(vec2i Position);
    void SetStatus(bool Status);
    void DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size = nullopt);
    void DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect);

protected:
    vec2i m_Position;
    vec2i m_Size;
    bool  m_IsAlive = true;
};