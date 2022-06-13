#include "HighscoreState.h"

HighscoreState::HighscoreState(shared_ptr<Font> MyFont) : GameState(eStateID::HIGHSCORE)
{
    m_Font = MyFont;
}

void HighscoreState::OnEnter()
{
    GameState::OnEnter();
    ReadScoresFromFile();

    sort(m_AllPlayersScores.begin(), m_AllPlayersScores.end(), [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second; });
}

void HighscoreState::FreeResources()
{
    m_AllPlayersScores.clear();
}

void HighscoreState::OnKeyDown(SDL_Scancode KeyCode)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        FreeResources();
        m_NextStateID = eStateID::MAINMENU;
    }
}


void HighscoreState::Update(float DeltaTime) {}

void HighscoreState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    m_Font->DrawText(pRenderer, 5, 115, 100, "HIGHSCORE TABLE");

    int x_spacing = 300;
    int y_spacing = 30;

    for (size_t i = 0; i < m_AllPlayersScores.size(); ++i)
    {
        m_Font->DrawText(pRenderer, 2, 220, 150 + (i + 1) * y_spacing, m_AllPlayersScores[i].first.c_str());
        m_Font->DrawText(pRenderer, 2, 220 + x_spacing, 150 + (i + 1) * y_spacing, ToString(m_AllPlayersScores[i].second).c_str());
    }

    SDL_RenderPresent(pRenderer);
}

void HighscoreState::WriteScoreToFile()
{
    fstream stream;
    // otwieramy plik w trybie 'app', bo bedziemy go modyfikowali
    stream.open((DataPath / m_FileName).string().c_str(), std::ios::app);

    char endline[] = "\n";

    int line_num_to_rewrite = 0;
    int previous_score = 0;
    bool rewrite_player_score = false;

    if (stream)
    {
        // sprawdzenie, czy gracz o danej nazwie znajduje sie juz w tabeli wynikow
        // jesli tak, to sprawdzamy czy biezacy wynik jest wyzszy niz poprzedni - jesli tak, tworzymy nowa tabele, w ktorej go uaktualnimy
        if (SearchForPlayerInHighscoreTable(GetCurrentPlayerName(), line_num_to_rewrite, previous_score))
        {
            if (GetCurrentPlayerScore() > previous_score)
            {
                rewrite_player_score = true;
                RewriteValueInFile(m_FileName, line_num_to_rewrite, GetCurrentPlayerScore());
            }
        }
        // jesli nie znaleziono gracza o podanej nazwie, to zapisujemy go do biezacej tabeli
        else
        {
            stream << GetCurrentPlayerName();
            stream << endline;

            stream << GetCurrentPlayerScore();
            stream << endline;
        }
        stream.close();
    }

    // jesli uaktualnialismy wynik gracza, to usuwamy poprzednia, nieaktualna juz, tabele wynikow
    if (rewrite_player_score)
    {
        std::remove((DataPath / m_FileName).string().c_str());
        std::rename((DataPath / ("tmp_" + m_FileName)).string().c_str(), (DataPath / m_FileName).string().c_str());
    }
}

bool HighscoreState::SearchForPlayerInHighscoreTable(string PlayerName, int& score_line_num, int& current_score)
{
    fstream stream;
    stream.open((DataPath / m_FileName).string().c_str(), std::ios::in);

    if (stream)
    {
        while (!stream.eof())
        {
            string line;
            getline(stream, line);
            score_line_num++;

            if (line.find(PlayerName) != std::string::npos)
            {
                score_line_num++;
                stream >> current_score;

                return true;
            }
        }
    }

    return false;
}

bool HighscoreState::ReadScoresFromFile()
{
    fstream stream;
    stream.open((DataPath / m_FileName).string().c_str(), std::ios::in);

    if (!stream)
    {
        printf("Could not open the file!\n");
        return false;
    }

    string player_name;
    int player_score = 0;
    pair<string, int> tmp;

    while (!stream.eof())
    {
        stream >> player_name;
        stream >> player_score;

        tmp.first = player_name;
        tmp.second = player_score;
        m_AllPlayersScores.push_back(tmp);
    }
 
    m_AllPlayersScores.pop_back();

    return true;
}

void HighscoreState::SetCurrentPlayerData(string PlayerName, int PlayerScore)
{
    m_CurrentPlayerName = PlayerName;
    m_CurrentScore = PlayerScore;
}

string HighscoreState::GetCurrentPlayerName() const
{
    return m_CurrentPlayerName;
}

int HighscoreState::GetCurrentPlayerScore() const
{
    return m_CurrentScore;
}


//----------------------------------------------------------------------
void RewriteValueInFile(string FileName, int LineNum, int ValueToRewrite)
{
    string current_filepath = (DataPath / FileName).string();
    string new_filepath = (DataPath / ("tmp_" + FileName)).string();

    fstream new_file;
    new_file.open(new_filepath.c_str(), std::ios::out);

    fstream prev_file;
    prev_file.open(current_filepath.c_str(), std::ios::in);

    if (!new_file || !prev_file)
    {
        printf("Could not open the file(s)!\n");
        return;
    }

    string line;
    bool keep_reading = true;
    int current_line = 1;
    char endline[] = "\n";

    do
    {
        // odczytujemy zawartosc tabeli wynikow
        prev_file >> line;
        // sprawdzamy czy dotarlismy do konca pliku tekstowego
        if (prev_file.eof())
        {
            keep_reading = false;
        }
        // uaktualniamy wynik danego gracza w nowej tabeli wynikow
        else if (current_line == LineNum)
        {
            new_file << ValueToRewrite;
            new_file << endline;
        }
        // wyniki pozostalych graczy zapisujemy do nowej tabeli wynikow bez zmian
        else
        {
            new_file << line;
            new_file << endline;
        }

        current_line++;

    } while (keep_reading);

    prev_file.close();
    new_file.close();
}