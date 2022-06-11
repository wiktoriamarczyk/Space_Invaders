#pragma once
#include "GameState.h"

class HighscoreState : public GameState
{
public:
    HighscoreState(shared_ptr<Font> MyFont);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
    void FreeResources();

    bool SearchForPlayerInHighscoreTable(string PlayerName, int& score_line_num, int& current_score);
    void WriteScoreToFile();
    bool ReadScoresFromFile();

    void SetCurrentPlayerData(string PlayerName, int PlayerScore);
    string GetCurrentPlayerName()const;
    int GetCurrentPlayerScore()const;

private:
    string                    m_CurrentPlayerName;
    int                       m_CurrentScore = 0;
    string                    m_FileName = "Highscore.txt";
    vector<pair<string, int>> m_AllPlayersScores;
};


void RewriteValueInFile(string FileName, int LineNum, int ValueToRewrite);