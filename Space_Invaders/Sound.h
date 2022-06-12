#pragma once
import Module_Common;

#include<SDL.h>;
#include<SDL_Mixer.h>;
#include<SDL_image.h>;
class Sound
{
public:
    Sound() = default;
    ~Sound();
    bool Load(const path & FileName,float Volume = 1.0f );
    void Play()const;
    string GetName()const;
    void FreeResources();
    bool LoadMusic(const string& FileName);
    void PlayMusic()const;

private:
    Mix_Chunk* m_pSoundData = nullptr;
    Mix_Music* m_pMusic = nullptr;
    string m_FileName;
};

