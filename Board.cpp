//
// Created by Berse on 9/20/2026.
//

#include "Board.h"
#include "iostream"

void Board::InitTokens()
{
    m_Tokens = new Token *[m_MaxRows]();
    for (auto i = 0; i < m_MaxRows; ++i) { m_Tokens[i] = new Token[m_MaxColumns](); }
}

void Board::DestroyTokens() const
{
    for (auto i = 0; i < m_MaxRows; ++i) { delete[] m_Tokens[i]; }
    delete[] m_Tokens;
}

void Board::DisplayBoard() const
{
    for (auto i = 0; i < m_MaxRows; ++i)
    {
        for (auto j = 0; j < m_MaxColumns; ++j) { std::cout << "| " << m_Tokens[i][j].GetTokenChar() << " "; }
        std::cout << "|\n";
    }
}

int Board::ConvertToColumnNumber(const int input) { return input - 1; }

int Board::FindEmptyRow(const int selectedColumn)
{
    for (int i = m_MaxRows - 1; i >= 0; --i)
    {
        if (m_Tokens[i][selectedColumn].GetTokenState() == TokenState::Inactive) { return i; }
    }
    return -1;
}

void Board::AddTokenToColumn(const int row, const int &column, const bool isRedPlayer)
{
    m_TokensAdded++;
    m_Tokens[row][column].SetTokenState(isRedPlayer ? TokenState::Red : TokenState::Yellow);
}

bool Board::IsColumnValid(const int column)
{
    m_IsInputValid = column >= 0 && column < m_MaxColumns;
    return m_IsInputValid;
}

bool Board::IsRowFull(const int row) { return row == -1; }

bool Board::CheckTokenState(const int x, const int y)
{
    if (x >= m_MaxRows ||
        y >= m_MaxColumns ||
        x < 0 ||
        y < 0) { return false; }
    return m_Tokens[x][y].GetTokenState() == m_CurrentPlayerState;
}

bool Board::CheckVertical(const int x, const int y)
{
    int count{1};
    bool down{true};
    bool up{true};
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(x + i, y) && down) count++;
        else down = false;

        if (CheckTokenState(x - i, y) && up) count++;
        else up = false;

        if (!down && !up)
            break;
    }
    return count >= 4;
}

bool Board::CheckHorizontal(const int x, const int y)
{
    int count{1};
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(x, y + i)) count++;
        else break;
    }
    return count >= 4;
}

bool Board::CheckDiagonal(int x, int y)
{
    int count{1};
    bool right{true};
    bool left{true};

    //Left Horizontal
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(x + i, y + i) && right) count++;
        else right = false;

        if (CheckTokenState(x - i, y - i) && left) count++;
        else left = false;

        if (!right && !left) break;
    }

    if (count >= 4) return true;

    count = 1;
    right = left = true;

    //Right Horizontal
    for (auto i = 1; i < 4; ++i)
    {
        if (CheckTokenState(x + i, y - i) && right) count++;
        else right = false;

        if (CheckTokenState(x - i, y + i) && left) count++;
        else left = false;

        if (!right && !left) break;
    }

    return count >= 4;
}

void Board::CheckWin(const int row, const int column, const bool isRedPlayer)
{
    if (CheckVertical(row, column) ||
        CheckHorizontal(row, column) ||
        CheckDiagonal(row, column))
    {
        DisplayBoard();
        const std::string playerName = isRedPlayer ? "Red" : "Yellow";
        std::cout << "\nPlayer " << playerName << " Wins\n\n";
        m_IsGameOver = true;
    }
}

void Board::PlayGame(const int &input, const bool &isRedPlayer)
{
    const int selectedColumn = ConvertToColumnNumber(input);
    if (!IsColumnValid(selectedColumn))
    {
        std::cout << "\n Wrong Input... Try Again";
        return;
    }

    const int emptyRow = FindEmptyRow(selectedColumn);
    if (IsRowFull(emptyRow))
    {
        m_IsInputValid = false;
        std::cout << "\nColumn Full.. Try another column!";
        return;
    }
    AddTokenToColumn(emptyRow, ConvertToColumnNumber(input), isRedPlayer);
    m_CurrentPlayerState = isRedPlayer ? TokenState::Red : TokenState::Yellow;

    CheckWin(emptyRow, selectedColumn, isRedPlayer);
}

bool Board::CheckGameOver()
{
    if (m_TokensAdded == m_MaxRows * m_MaxColumns && !m_IsGameOver)
    {
        std::cout << "\n Its a Draw!";
        m_IsGameOver = true;
    }
    return m_IsGameOver;
}
