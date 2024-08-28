#ifndef RPAREN_H
#define RPAREN_H


class RParen : public Token
{
public: 
    RParen()
    {
        set_token_str(")");
        set_token_type(RPAREN);
    }

    RParen(string s)
    {
        set_token_str(s);
        set_token_type(RPAREN);
    }

    TokenType get_token_type()
    {
        return RPAREN; 
    }
};

#endif