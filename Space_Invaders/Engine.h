#pragma once
#include "GameState.h"
#include "Sound.h"
#include "Texture.h"
#include "PlayerData.h"

class Engine
{
public:
    Engine() = default;
    ~Engine();
    static Engine* GetSingleton();
    bool Initialize();
    void Loop();
    void ChangeState(eStateID StateID);
    void ExitGame();
    void PlaySound(const path& FileName, float Volume = 1.0f);
    void FreeSounds();
    shared_ptr<Texture> GetTexture(const path& FileName)const;
    void DisplayTexture(const path& FileName, vec2 Position, DisplayParameters Param = {});
    void DestroyTextures();
    vec2i GetTextureSize(const path& FileName)const;
    vec2i GetMousePos()const;


private:
    void TextureLoadThread();
    void LoadResources();

    using TexturesVec = vector<shared_ptr<Texture>>;

    static Engine*                pSingleton;
    bool                          m_IsRunning = true;
    SDL_Renderer*                 m_pRenderer = nullptr;
    SDL_Window*                   m_pWindow = nullptr;
    GameState*                    m_pCurrentState = nullptr;
    vector<unique_ptr<GameState>> m_AllStates;
    vector<shared_ptr<Sound>>     m_LoadedSounds;
    TexturesVec                   m_LoadedTextures;
    mutable mutex                 m_EngineMutex;
    vector<path>                  m_TexturesToLoad;
    vector<thread>                m_LoadingThreads;
};