#ifndef RELATIONAL_H
#define RELATIONAL_H

class Relational : public Token 
{
public: 
    Relational()
    {
        set_token_str(string());
        set_token_type(RELATIONAL);
    }

    Relational(string s)
    {
        set_token_str(s);
        set_token_type(RELATIONAL);
    }

    TokenType get_token_type()
    {
        return RELATIONAL;
    }

};

#endif