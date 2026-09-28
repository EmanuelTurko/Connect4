//
// Created by Berse on 9/20/2026.
//

#ifndef CONNECT4_TOKEN_H
#define CONNECT4_TOKEN_H

enum class TokenState {
    Inactive = ' ',
    Red = 'R',
    Yellow = 'Y'
};

class Token {
private:
    TokenState m_State;

public:
    Token() { m_State = TokenState::Inactive; }

    virtual ~Token()
    = default;

    void SetTokenState(const TokenState newState) { m_State = newState; }
    [[nodiscard]] TokenState GetTokenState() const { return m_State; }
    [[nodiscard]] char GetTokenChar() const { return static_cast<char>(m_State); }
};

#endif //CONNECT4_TOKEN_H
