//
// Created by Berse on 9/19/2026.
//

#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H
#include "Token.h"
#include <SFML/System/Vector2.hpp>


class Board
{
private:
    static constexpr sf::Vector2i m_BoardSize{7,6};
    bool m_IsGameOver{};
    Token **m_Tokens{};
    bool m_IsInputValid{};
    int m_TokensAdded{};
    TokenState m_CurrentPlayerState{};

    void InitTokens();

    void DestroyTokens() const;

    int ConvertToColumnNumber(int input);

    int FindEmptyRow(int selectedCol);

    void AddTokenToColumn(int row, int col, bool isRedPlayer);

    bool IsColumnValid(int col);

    bool IsRowFull(int row);

    bool CheckTokenState(int col, int row);

    bool CheckHorizontal(int col, int row);

    bool CheckVertical(int col, int row);

    bool CheckDiagonal(int col, int row);

    void CheckWin(int col, int row, bool isRedPlayer);

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
};


#endif //CONNECT4_BOARD_H
