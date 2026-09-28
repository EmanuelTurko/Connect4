#ifndef CONNECT4_GAME_H
#define CONNECT4_GAME_H

#include <optional>
#include "Board.h"
#include "Renderer.h"

class Game
{
private:
    Board m_Board{};
    Renderer m_Renderer{};
    bool m_IsRedPlayer{true}; // red always starts

    void Update()
    {
        m_Renderer.Render(m_Board, m_IsRedPlayer);

        if (m_Renderer.IsReplayClicked())
        {
            m_Board.Reset();
            m_IsRedPlayer = true;
            return; // don't also count this click as a move
        }

        if (const std::optional<int> col = m_Renderer.GetClickedColumn())
        {
            m_Board.PlayGame(*col, m_IsRedPlayer);
            if (m_Board.CheckInputValidity()) { m_IsRedPlayer = !m_IsRedPlayer; }
        }
    }

public:
    void Run() { while (m_Renderer.IsWindowOpen()) { Update(); } }
};

#endif //CONNECT4_GAME_H