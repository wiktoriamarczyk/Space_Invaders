#pragma once
#include "Common.h"
#include "vec2.h"

class Texture
{
public:
    Texture(SDL_Renderer* pRenderer);
    ~Texture();
    bool Load(const string& FileName);
    void Display(vec2i Position, optional<vec2i> Size = nullopt)const;
    void Display(SDL_Rect srcrect, SDL_Rect dstrect);
    void FreeResources();
    vec2i GetSize();
    string GetName();

private:
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Surface*  m_pImage = nullptr;
    SDL_Texture*  m_pTexture = nullptr;
    vec2i         m_Size;
    string        m_FileName;
};