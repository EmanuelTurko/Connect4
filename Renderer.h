//
// Created by Berse on 9/21/2026.
//

#ifndef CONNECT4_RENDERER_H
#define CONNECT4_RENDERER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>
#include "Board.h"


class Renderer
{
private:
    static constexpr float m_CellSize{100.f};
    static constexpr float m_Padding{15.f};
    static constexpr sf::Vector2u m_WindowSize{700, 600};
    static constexpr sf::Vector2f m_ReplayButtonPosition{350.f, 300.f};
    static constexpr sf::Vector2f m_ReplayButtonSize{200.f, 60.f};
    static constexpr auto m_FontPath{"assets/font/Roboto-Med.ttf"};

    sf::RenderWindow m_Window{};
    std::optional<int> m_ClickedCol{};
    sf::Font m_Font{};
    sf::RectangleShape m_ReplayButton{m_ReplayButtonSize};

    bool m_ReplayClicked{false};

    void InitWindow();

    void InitFont();

    void InitReplayButton();

public:
    Renderer();

    virtual ~Renderer() = default;

    sf::Color GetColorForState(TokenState state) const;

    void Render(const Board &board, bool isRedPlayer);

    bool IsWindowOpen() const { return m_Window.isOpen(); }

    std::optional<int> GetClickedColumn() const { return m_ClickedCol; }
    [[nodiscard]] bool IsReplayClicked() const { return m_ReplayClicked; }
};
#endif //CONNECT4_RENDERER_H
