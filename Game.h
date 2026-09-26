//
// Created by Berse on 9/20/2026.
//
#pragma once
#include "Board.h"
#include "iostream"
#include "Renderer.h"

#ifndef CONNECT4_GAME_H
#define CONNECT4_GAME_H


class Game
{
private:
    bool m_IsGameOver{};
    int m_Input{};
    Board m_Board{};
    bool m_IsRedPlayer{};
    Renderer m_Renderer;

    void Update()
    {
        m_Renderer.Render(m_Board);


        //m_Board.DisplayBoard();
      /*  do
        {
            GetInput();
            m_Board.PlayGame(m_Input, m_IsRedPlayer);
        } while (!m_Board.CheckInputValidity());
        {
            if (m_Board.CheckGameOver()) m_IsGameOver = true;
        }
        m_IsRedPlayer = !m_IsRedPlayer;*/
    }

    void GetInput()
    {
        const std::string playerName = m_IsRedPlayer ? "Red" : "Yellow";
        std::cout << "\n" << playerName << "Input : ";
        std::cin >> m_Input;
    }

public:
    // Constructor and Destructor
    Game()
    {
        m_IsGameOver = false;
        m_IsRedPlayer = false;
    }

    virtual ~Game()
    {
    }

    // Main Game Loop Method
    void Run()
    {
        while (m_Renderer.IsWindowOpen())
        {
            Update();
        }
       // while (!m_IsGameOver) { Update(); }
    }
};

#endif //CONNECT4_GAME_H
