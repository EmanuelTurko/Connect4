#include "Board.h"


void Board::PlayGame(const int col, const bool isRedPlayer)
{
    m_IsInputValid = false;
    if (m_IsGameOver || !IsColumnValid(col)) return;

    const int row = FindEmptyRow(col);
    if (IsColumnFull(row)) return;

    AddTokenToColumn(row, col, isRedPlayer);
    m_IsInputValid = true;

    CheckWin(col, row);
    if (!m_IsGameOver) CheckDraw();
}

void Board::AddTokenToColumn(const int row, const int col, const bool isRedPlayer)
{
    m_CurrentPlayerState = isRedPlayer ? TokenState::Red : TokenState::Yellow;
    m_Tokens[row][col].SetTokenState(m_CurrentPlayerState);
    ++m_TokensAdded;
}

bool Board::IsColumnValid(const int col) const
{
    return col >= 0 && col < m_BoardSize.x;
}

int Board::FindEmptyRow(const int col) const
{
    if (!IsColumnValid(col)) return -1;

    for (int row = m_BoardSize.y - 1; row >= 0; --row)
    {
        if (m_Tokens[row][col].GetTokenState() == TokenState::Inactive) return row;
    }
    return -1;
}

void Board::Reset()
{
    for (auto &row : m_Tokens)
        for (auto &token : row)
            token.SetTokenState(TokenState::Inactive);

    m_IsGameOver = false;
    m_IsInputValid = false;
    m_TokensAdded = 0;
    m_CurrentPlayerState = TokenState::Inactive;
    m_Winner = TokenState::Inactive;
}


bool Board::CheckTokenState(const int col, const int row) const
{
    if (col < 0 || col >= m_BoardSize.x || row < 0 || row >= m_BoardSize.y) return false;
    return m_Tokens[row][col].GetTokenState() == m_CurrentPlayerState;
}

bool Board::CheckHorizontal(const int col, const int row) const
{
    int count{1};
    bool right{true};
    bool left{true};
    for (int i = 1; i < 4; ++i)
    {
        if (right && CheckTokenState(col + i, row)) ++count;
        else right = false;

        if (left && CheckTokenState(col - i, row)) ++count;
        else left = false;

        if (!right && !left) break;
    }
    return count >= 4;
}

bool Board::CheckVertical(const int col, const int row) const
{
    int count{1};
    for (int i = 1; i < 4; ++i)
    {
        if (CheckTokenState(col, row + i)) ++count;
        else break;
    }
    return count >= 4;
}

bool Board::CheckDiagonal(const int col, const int row) const
{
    // "\" diagonal: down-right and up-left
    int count{1};
    bool forward{true};
    bool backward{true};
    for (int i = 1; i < 4; ++i)
    {
        if (forward && CheckTokenState(col + i, row + i)) ++count;
        else forward = false;

        if (backward && CheckTokenState(col - i, row - i)) ++count;
        else backward = false;

        if (!forward && !backward) break;
    }
    if (count >= 4) return true;

    // "/" diagonal: up-right and down-left
    count = 1;
    forward = backward = true;
    for (int i = 1; i < 4; ++i)
    {
        if (forward && CheckTokenState(col + i, row - i)) ++count;
        else forward = false;

        if (backward && CheckTokenState(col - i, row + i)) ++count;
        else backward = false;

        if (!forward && !backward) break;
    }
    return count >= 4;
}

void Board::CheckWin(const int col, const int row)
{
    if (CheckHorizontal(col, row) || CheckVertical(col, row) || CheckDiagonal(col, row))
    {
        m_Winner = m_CurrentPlayerState;
        m_IsGameOver = true;
    }
}

void Board::CheckDraw()
{
    if (m_TokensAdded == m_BoardSize.x * m_BoardSize.y) m_IsGameOver = true;
}