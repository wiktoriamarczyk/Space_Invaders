#include "Texture.h"

Texture::Texture(SDL_Renderer* pRenderer)
{
    m_pRenderer = pRenderer;
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_FreeSurface(m_pImage);

    m_pTexture = nullptr;
    m_pImage = nullptr;
}

bool Texture::Load(const path& FileName)
{
    m_FileName = FileName.string();
    m_pImage = IMG_Load((DataPath / FileName).string().c_str());

    if (!m_pImage)
    {
        printf("Texture could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);

    if (SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Size.x, &m_Size.y) != 0)
    {
        printf("Texture error! SDL_Error: %s\n", SDL_GetError());
        throw 1;
    }

    return true;
}

void Texture::Display(vec2 Position, DisplayParameters Param)const
{
    //int value = 0;
    //if( w.has_value() )
    //    value = w.value();

    //if (w)
    // value = *w;

    vec2 tmp = vec2(Param.DisplaySize.value_or(m_Size)) * Param.DrawScale;
    SDL_Rect DstRect = {Position.x, Position.y, tmp.x, tmp.y };

    SDL_Rect SrcRect = {Param.SrcTopLeft.x * m_Size.x, Param.SrcTopLeft.y * m_Size.y, Param.SrcSize.x * m_Size.x, Param.SrcSize.y * m_Size.y };

    if (Param.DrawColor.R != 1 || Param.DrawColor.G != 1 || Param.DrawColor.B != 1)
    {
        SDL_SetTextureColorMod(m_pTexture, Uint8(Param.DrawColor.R*255), Uint8(Param.DrawColor.G*255), Uint8(Param.DrawColor.B*255));
    }

    if (Param.DrawColor.A != 1)
    {
        SDL_SetTextureAlphaMod(m_pTexture, Uint8(Param.DrawColor.A * 255));
    }

    if (Param.DrawMode == eDrawMode::ADDITIVE)
        SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_ADD);
    else
        SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);
    
    SDL_RenderCopy(m_pRenderer, m_pTexture, &SrcRect, &DstRect);
}

void Texture::FreeResources()
{
    Texture::~Texture();
}

vec2i Texture::GetSize()
{
    if (m_pTexture)
    {
        return m_Size;
    }
    else
    {
        printf("Texture error! \n");
        throw 1;
    }

    return m_Size;
}

string Texture::GetName()
{
    return m_FileName;
}