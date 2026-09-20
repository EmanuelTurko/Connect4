//
// Created by Berse on 9/20/2026.
//
#pragma once
#include "Board.h"
#include "iostream"

#ifndef CONNECT4_GAME_H
#define CONNECT4_GAME_H


class Game {
private:
    bool m_IsGameOver{};
    int m_Input{};
    Board m_Board{};

    void Update()
    {
        GetInput();
        m_Board.PlayGame(m_Input);
        if (m_Board.CheckGameOver()) m_IsGameOver = true;

    }

    void GetInput()
    {
        std::cout << "Input : ";
        std::cin >> m_Input;
    }

public:
    // Constructor and Destructor
    Game()
    {
        m_IsGameOver = false;
    }

    virtual ~Game()
    {
    }

    // Main Game Loop Method
    void Run()
    {
        while (!m_IsGameOver) {
            Update();
        }
    }
};

#endif //CONNECT4_GAME_H
