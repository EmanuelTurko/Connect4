#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H
#include <array>
#include <SFML/System/Vector2.hpp>
#include "Token.h"

class Board
{
private:
    static constexpr sf::Vector2i m_BoardSize{7, 6};   // x = columns, y = rows

    std::array<std::array<Token, m_BoardSize.x>, m_BoardSize.y> m_Tokens{};   // indexed [row][col]

    bool m_IsGameOver{};
    bool m_IsInputValid{};
    int m_TokensAdded{};
    TokenState m_CurrentPlayerState{TokenState::Inactive};
    TokenState m_Winner{TokenState::Inactive};

    void AddTokenToColumn(int row, int col, bool isRedPlayer);
    [[nodiscard]] bool IsColumnValid(int col) const;
    [[nodiscard]] static bool IsColumnFull(int row) { return row == -1; }

    [[nodiscard]] bool CheckTokenState(int col, int row) const;
    [[nodiscard]] bool CheckHorizontal(int col, int row) const;
    [[nodiscard]] bool CheckVertical(int col, int row) const;
    [[nodiscard]] bool CheckDiagonal(int col, int row) const;
    void CheckWin(int col, int row);
    void CheckDraw();

public:
    void PlayGame(int col, bool isRedPlayer);
    void Reset();

    [[nodiscard]] int FindEmptyRow(int col) const;
    [[nodiscard]] bool CheckInputValidity() const { return m_IsInputValid; }
    [[nodiscard]] bool IsGameOver() const { return m_IsGameOver; }
    [[nodiscard]] TokenState GetWinner() const { return m_Winner; }
    [[nodiscard]] sf::Vector2i GetBoardSize() const { return m_BoardSize; }

    [[nodiscard]] TokenState GetTokenStateAt(const sf::Vector2i position) const
    {
        return m_Tokens[position.y][position.x].GetTokenState();
    }
};

#endif //CONNECT4_BOARD_H