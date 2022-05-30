#include "Sound.h"

Sound::~Sound()
{
    Mix_FreeChunk(m_pSoundData);
    m_pSoundData = nullptr;
    Mix_FreeMusic(m_pMusic);
    m_pMusic = nullptr;
}

bool Sound::Load(const path& FileName, float Volume )
{
    m_FileName = FileName.string();

    m_pSoundData = Mix_LoadWAV((DataPath/FileName).string().c_str());

    Mix_VolumeChunk( m_pSoundData, int(Volume * MIX_MAX_VOLUME) );
    if (m_pSoundData == nullptr)
    {
        printf("Sound could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Sound::Play()const
{
    Mix_PlayChannel(-1, m_pSoundData, 0);
}

string Sound::GetName()const
{
    return m_FileName;
}

void Sound::FreeResources()
{
    Sound::~Sound();
}

/*
bool Sound::LoadMusic(const string& FileName)
{
    m_FileName = FileName;
    m_pMusic = Mix_LoadMUS(("../Data/" + FileName).c_str());
    if (m_pMusic == nullptr)
    {
        printf("Music could not be loaded! SDL_Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

void Sound::PlayMusic() const
{
    Mix_PlayMusic(m_pMusic, -1);
}
*/
