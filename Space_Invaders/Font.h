#pragma once
import Module_Common;

#include<SDL.h>;
#include<SDL_Mixer.h>;
#include<SDL_image.h>;
struct CharacterData
{
    vector<string> m_ImageData;
    char m_Character;
};


class Font
{
    vector<CharacterData> m_Dictionary;
public:
    void LoadFont(const string& FileName);
    const CharacterData* FindCharacter(char Character)const;
    void DrawText(SDL_Renderer* pRenderer, int PixelSize, int PosX, int PosY, const char* Text, Color MyColor = { 255.f,255.f,255.f });
};


bool ReadLine(fstream& FileStream, string& OutString, int ExpectedSize);
bool LoadSingleCharacter(fstream& FileStream, CharacterData& DataOut);
vector<CharacterData> FillFontVector(const string& FileName);
void DrawLine(SDL_Renderer* pRenderer, int PixelSize, int PosX, int PosY, const string& Pixels);
void DrawLines(SDL_Renderer* pRenderer, int PixelSize, int PosX, int PosY, const vector<string>& Lines, Color MyColor);
string ToString(int value);

