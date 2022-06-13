#pragma once
import Module_Common;
#include "vec2.h"

class Texture
{
public:
    Texture(SDL_Renderer* pRenderer);
    ~Texture();
    bool Load(const path& FileName);
    void Display(vec2 Position, DisplayParameters Param = {})const;
    void FreeResources();
    vec2i GetSize();
    string GetName();
    void PrepareTexture();

private:
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Surface*  m_pImage = nullptr;
    SDL_Texture*  m_pTexture = nullptr;
    vec2i         m_Size;
    string        m_FileName;
};