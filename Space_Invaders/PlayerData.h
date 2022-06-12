#pragma once
import Module_Common;
#include "HighscoreState.h"

class PlayerData
{
public:
    PlayerData(HighscoreState& Highscore);
    string GetName()const;
    int GetScore()const;
    void SetName(string Name);
    void SetScore(int Score);
    void SendDataToHighscore();

private:
    HighscoreState& m_Highscore;
    string          m_Name;
    int             m_Score;
};


