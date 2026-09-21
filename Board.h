//
// Created by Berse on 9/19/2026.
//

#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H
#include "Token.h"


class Board
{
private:
    static constexpr int m_MaxRows{6};
    static constexpr int m_MaxColumns{7};
    bool m_IsGameOver{};
    Token **m_Tokens{};
    bool m_IsInputValid{};
    int m_TokensAdded{};
    TokenState m_CurrentPlayerState{};


    void InitTokens();

    void DestroyTokens() const;

    int ConvertToColumnNumber(int input);

    int FindEmptyRow(int selectedColumn);

    void AddTokenToColumn(int row, const int &column, bool isRedPlayer);

    bool IsColumnValid(int column);

    bool IsRowFull(int row);

    bool CheckTokenState(int x, int y);

    bool CheckVertical(int x, int y);

    bool CheckHorizontal(int x, int y);

    bool CheckDiagonal(int x, int y);

    void CheckWin(int row, int column, bool isRedPlayer);

public:
    // Constructor and Destructor
    Board()
    {
        InitTokens();
        m_IsGameOver = false;
    }

    virtual ~Board() { DestroyTokens(); }

    void DisplayBoard() const;

    bool CheckGameOver();

    void PlayGame(const int &input, const bool &isRedPlayer);

    bool CheckInputValidity() { return m_IsInputValid; }

    int GetBoardLength() const { return m_MaxRows; }
    int GetBoardWidth() const { return m_MaxColumns; }
};


#endif //CONNECT4_BOARD_H
