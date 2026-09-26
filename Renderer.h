//
// Created by Berse on 9/21/2026.
//

#ifndef CONNECT4_RENDERER_H
#define CONNECT4_RENDERER_H
#include "SFML/Graphics/RenderWindow.hpp"


class Renderer
{
private:
    sf::RenderWindow m_Window{};
    static constexpr float m_CellSize{100.f};
    static constexpr float m_Padding{15.f};
public:


    Renderer(){ InitWindow();}
    virtual ~Renderer(){}

    void InitWindow()
    {
        m_Window.create(sf::VideoMode({700,600}),"Connect Four");
    }

    void Render(const Board& board)
    {
        m_Window.clear(sf::Color::Blue);
        for (auto row = 0; row < board.GetBoardSize().y;++row)
        {
            for (auto col = 0; col < board.GetBoardSize().x;++col)
            {
                sf::CircleShape circle(m_CellSize / 2.f - m_Padding);
                circle.setFillColor(sf::Color::White);
                circle.setPosition({m_CellSize * static_cast<float>(col) + m_Padding, m_CellSize * static_cast<float>(row) + m_Padding});
                m_Window.draw(circle);
            }
        }
        m_Window.display();

        while (const std::optional<sf::Event>& e = m_Window.pollEvent())
        {
            if (e->is<sf::Event::Closed>())
            {
                m_Window.close();
            }
            else if (const auto* click = e->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                {
                    const sf::Vector2i pixel = click->position;
                    const int col = pixel.x / static_cast<int>(m_CellSize);
                    const int row = pixel.y / static_cast<int>(m_CellSize);

                    std::cout << "pixel (" << pixel.x << ", " << pixel.y << ")"
            << "  ->  col " << col << ", row " << row << '\n';
                }
            }
        }



    }

    bool IsWindowOpen() const
    {
        return m_Window.isOpen();
    }


};
#endif //CONNECT4_RENDERER_H
