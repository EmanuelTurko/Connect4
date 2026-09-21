//
// Created by Berse on 9/20/2026.
//

#include "Board.h"
#include "iostream"

void Board::InitTokens()
{
    m_Tokens = new Token *[m_BoardSize.y]();
    for (auto i = 0; i < m_BoardSize.y; ++i) { m_Tokens[i] = new Token[m_BoardSize.x](); }
}

void Board::DestroyTokens() const
{
    for (auto i = 0; i < m_BoardSize.y; ++i) { delete[] m_Tokens[i]; }
    delete[] m_Tokens;
}

void Board::DisplayBoard() const
{
    for (auto i = 0; i < m_BoardSize.y; ++i)
    {
        for (auto j = 0; j < m_BoardSize.x; ++j) { std::cout << "| " << m_Tokens[i][j].GetTokenChar() << " "; }
        std::cout << "|\n";
    }
}

int Board::ConvertToColumnNumber(const int input) { return input - 1; }

int Board::FindEmptyRow(const int selectedCol)
{
    for (int i = m_BoardSize.y - 1; i >= 0; --i)
    {
        if (m_Tokens[i][selectedCol].GetTokenState() == TokenState::Inactive) { return i; }
    }
    return -1;
}

void Board::AddTokenToColumn(const int row, const int col, const bool isRedPlayer)
{
    m_TokensAdded++;
    m_Tokens[row][col].SetTokenState(isRedPlayer ? TokenState::Red : TokenState::Yellow);
}

bool Board::IsColumnValid(const int col)
{
    m_IsInputValid = col >= 0 && col < m_BoardSize.x;
    return m_IsInputValid;
}

bool Board::IsRowFull(const int row) { return row == -1; }

bool Board::CheckTokenState(const int col, const int row)
{
    if (col >= m_BoardSize.x ||
        row >= m_BoardSize.y ||
        col < 0 ||
        row < 0) { return false; }
    return m_Tokens[row][col].GetTokenState() == m_CurrentPlayerState;
}

bool Board::CheckHorizontal(const int col, const int row)
{
    int count{1};
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(col, row +i)) count++;
        else break;
    }
    return count >= 4;
}

bool Board::CheckVertical(const int col, const int row)
{
    int count{1};
    bool right{true};bool left{true};
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(col +i, row) && right) count++;
        else right = false;

        if (CheckTokenState(col -i, row) && left) count++;
        else left = false;

        if (!right && !left) break;
    }
    return count >= 4;
}

bool Board::CheckDiagonal(int col, int row)
{
    int count{1};
    bool right{true};
    bool left{true};

    //Left Horizontal
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(col + i, row + i) && right) count++;
        else right = false;

        if (CheckTokenState(col - i, row - i) && left) count++;
        else left = false;

        if (!right && !left) break;
    }

    if (count >= 4) return true;

    count = 1;
    right = left = true;

    //Right Horizontal
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(col + i, row - i) && right) count++;
        else right = false;

        if (CheckTokenState(col - i, row + i) && left) count++;
        else left = false;

        if (!right && !left) break;
    }

    return count >= 4;
}

void Board::CheckWin(const int col, const int row, const bool isRedPlayer)
{
    if (CheckHorizontal(col, row) ||
        CheckVertical(col, row) ||
        CheckDiagonal(col, row))
    {
        DisplayBoard();
        const std::string playerName = isRedPlayer ? "Red" : "Yellow";
        std::cout << "\nPlayer " << playerName << " Wins\n\n";
        m_IsGameOver = true;
    }
}

void Board::PlayGame(const int &input, const bool &isRedPlayer)
{
    const int col = ConvertToColumnNumber(input);
    if (!IsColumnValid(col))
    {
        std::cout << "\n Wrong Input... Try Again";
        return;
    }

    const int row = FindEmptyRow(col);
    if (IsRowFull(row))
    {
        m_IsInputValid = false;
        std::cout << "\nColumn Full.. Try another column!";
        return;
    }
    AddTokenToColumn(row, ConvertToColumnNumber(input), isRedPlayer);
    m_CurrentPlayerState = isRedPlayer ? TokenState::Red : TokenState::Yellow;

    CheckWin(col, row, isRedPlayer);
}

bool Board::CheckGameOver()
{
    if (m_TokensAdded == m_BoardSize.x * m_BoardSize.y  && !m_IsGameOver)
    {
        std::cout << "\n Its a Draw!";
        m_IsGameOver = true;
    }
    return m_IsGameOver;
}
