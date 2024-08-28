#ifndef LPAREN_H
#define LPAREN_H
#include "token.h"

class LParen : public Token
{
public: 
    LParen()
    {
        set_token_str("(");
        set_token_type(LPAREN);
    }

    LParen(string s)
    {
        set_token_str(s);
        set_token_type(LPAREN);
    }
    TokenType get_token_type()
    {
        return LPAREN; 
    }
};

#endif