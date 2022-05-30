#include "PlayerData.h"

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
