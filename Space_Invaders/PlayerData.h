#pragma once
#include "Common.h"

class PlayerData
{
public:
    string GetName()const;
    int GetScore()const;
    void SetName(string Name);
    void SetScore(int Score);

private:
    string m_Name;
    int    m_Score;
};

