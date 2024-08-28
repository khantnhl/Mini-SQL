#ifndef TOKENSTRING_H
#define TOKENSTRING_H
#include "token.h"
#include "logical.h"
#include "relational.h"
#include "LParen.h"
#include "RParen.h"

class TokenStr : public Token 
{
public: 
    TokenStr()
    {
        set_token_str(string());
        set_token_type(TOKENSTR);
    }

    TokenStr(string s)
    {
        set_token_str(s);
        set_token_type(TOKENSTR);
    }

    TokenType get_token_type() 
    {
        return TOKENSTR; //TOKEN
    }
    
    friend ostream& operator <<(ostream& outs, const TokenStr& t)
    {
        outs << t.get_token_str();
        return outs;
    }
};

#endif