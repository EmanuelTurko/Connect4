//
// Created by Berse on 9/19/2026.
//

#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H
#include "Token.h"
#include "iostream"


class Board
{
private:
    int m_Rows{};
    int m_Columns{};
    bool m_IsGameOver{};
    Token **m_Tokens{};

    void InitBoard()
    {
        m_Rows = 7;
        m_Columns = 6;
    }
    void InitTokens()
    {
        m_Tokens = new Token *[m_Columns]();
        for (auto i = 0; i < m_Columns; ++i) { m_Tokens[i] = new Token[m_Rows](); }
    }

    void DestroyTokens()
    {
        for (auto i = 0; i < m_Columns; ++i) { delete[] m_Tokens[i]; }
        delete[] m_Tokens;
    }

    void DisplayBoard() const
    {
        for (auto i = 0; i < m_Rows; ++i)
        {
            for (auto j = 0; j < m_Columns; ++j) { std::cout << "| " << m_Tokens[i][j].GetTokenChar() << " "; }
            std::cout << "|\n";
        }
    }

    int ConvertToColumnNumber(const int &input) { return input - 1; }

    int FindEmptyRow(const int &selectedColumn)
    {
        int emptyRowIndex{};

        for (int i = m_Rows - 1; i >= 0; --i)
        {
            if (m_Tokens[selectedColumn][i].GetTokenState() == TokenState::Inactive)
            {
                emptyRowIndex = i;
                break;
            }
        }
        return emptyRowIndex;
    }

    void AddTokenToColumn(const int &selectedColumn)
    {
        m_Tokens[selectedColumn][FindEmptyRow(selectedColumn)].SetTokenState(TokenState::Active);
    }

public:
    // Constructor and Destructor
    Board()
    {
        InitTokens();
        m_IsGameOver = false;
    }

    virtual ~Board() { DestroyTokens(); }


    void PlayGame(const int &input)
    {
        AddTokenToColumn(ConvertToColumnNumber(input));
        DisplayBoard();
    }

    bool CheckGameOver() { return m_IsGameOver; }

    int GetBoardLength() const { return m_Rows; }
    int GetBoardWidth() const { return m_Columns; }
};


#endif //CONNECT4_BOARD_H
