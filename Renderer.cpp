//
// Created by Berse on 9/28/2026.
//

#include "Renderer.h"

void Renderer::InitWindow() { m_Window.create(sf::VideoMode({m_WindowSize}), "Connect Four"); }

void Renderer::InitFont() { if (!m_Font.openFromFile(m_FontPath)) std::cerr << "Could not find font." << std::endl; }

void Renderer::InitReplayButton()
{
    m_ReplayButton.setOrigin(m_ReplayButton.getSize() / 2.f);
    m_ReplayButton.setPosition(m_ReplayButtonPosition);
    m_ReplayButton.setFillColor(sf::Color(40, 40, 40));
    m_ReplayButton.setOutlineColor(sf::Color::White);
    m_ReplayButton.setOutlineThickness(3.f);
}

Renderer::Renderer()
{
    InitWindow();
    InitFont();
    InitReplayButton();
}

sf::Color Renderer::GetColorForState(const TokenState state) const
{
    switch (state)
    {
        case TokenState::Red: return sf::Color::Red;
        case TokenState::Yellow: return sf::Color::Yellow;
        default: return sf::Color::White;
    }
}

void Renderer::Render(const Board &board, const bool isRedPlayer)
{
    m_ClickedCol.reset();
    m_ReplayClicked = false;

    while (const std::optional<sf::Event> &e = m_Window.pollEvent())
    {
        if (e->is<sf::Event::Closed>()) { m_Window.close(); } else if (const auto *click = e->getIf<
            sf::Event::MouseButtonPressed>())
        {
            if (click->button == sf::Mouse::Button::Left)
            {
                const sf::Vector2f clickPosition(click->position);
                if (board.IsGameOver() && m_ReplayButton.getGlobalBounds().contains(clickPosition))
                    m_ReplayClicked = true;
                else m_ClickedCol = click->position.x / static_cast<int>(m_CellSize);
            }
        }
    }

    int previewRow = -1;
    const sf::Vector2i mouse = sf::Mouse::getPosition(m_Window);
    const int hoverCol = mouse.x / static_cast<int>(m_CellSize);
    if (!board.IsGameOver() && mouse.x >= 0 && hoverCol < board.GetBoardSize().x)
    {
        previewRow = board.FindEmptyRow(hoverCol);
    }

    m_Window.clear(sf::Color::Blue);
    for (auto row = 0; row < board.GetBoardSize().y; ++row)
    {
        for (auto col = 0; col < board.GetBoardSize().x; ++col)
        {
            sf::Color color = GetColorForState(board.GetTokenStateAt({col, row}));
            if (col == hoverCol && row == previewRow)
            {
                color = isRedPlayer ? sf::Color(255, 150, 150) : sf::Color(255, 255, 150);
            }

            sf::CircleShape circle(m_CellSize / 2.f - m_Padding);
            circle.setFillColor(color);
            circle.setPosition({
                m_CellSize * static_cast<float>(col) + m_Padding,
                m_CellSize * static_cast<float>(row) + m_Padding
            });
            m_Window.draw(circle);
        }
    }

    if (board.IsGameOver())
    {
        sf::RectangleShape overlay({m_WindowSize.x, m_WindowSize.y});
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        m_Window.draw(overlay);

        std::string message = "Draw!";
        if (board.GetWinner() == TokenState::Red) message = "Red Wins!";
        if (board.GetWinner() == TokenState::Yellow) message = "Yellow Wins!";

        sf::Text text(m_Font, message, 64);
        text.setFillColor(sf::Color::White);

        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.position + bounds.size / 2.f);
        text.setPosition({350.f, 200.f});

        m_Window.draw(text);

        m_Window.draw(m_ReplayButton);

        sf::Text label(m_Font, "Replay", 32);
        const sf::FloatRect lb = label.getLocalBounds();
        label.setOrigin(lb.position + lb.size / 2.f);
        label.setPosition(m_ReplayButton.getPosition());
        m_Window.draw(label);
    }
    m_Window.display();
}
