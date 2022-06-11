#include "PlayerData.h"
#include "Font.h"

PlayerData::PlayerData(HighscoreState& Highscore) : m_Highscore(Highscore) 
{
}

string PlayerData::GetName() const
{
    return m_Name;
}

int PlayerData::GetScore() const
{
    return m_Score;
}

void PlayerData::SetName(string Name)
{
    m_Name = Name;
}

void PlayerData::SetScore(int Score)
{
    m_Score = Score;
}

void PlayerData::SendDataToHighscore()
{
    m_Highscore.SetCurrentPlayerData(m_Name, m_Score);
    m_Highscore.WriteScoreToFile();
}
