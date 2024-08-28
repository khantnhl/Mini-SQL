#ifndef TOKEN_H
#define TOKEN_H

#include "../../includes/table/typedefs.h"

#include<iostream>
#include<string>

using namespace std; 

enum TokenType
{
    // TOKEN,
    LPAREN,
    RPAREN,
    TOKENSTR,
    // OPERATOR,
    RELATIONAL,
    LOGICAL, 

    // RESULT_SET,
    
    // TOKEN_NUMBER,
    // TOKEN_ALPHA,
    // TOKEN_SPACE,
    // TOKEN_OPERATOR,
    // TOKEN_PUNC,
    // TOKEN_UNKNOWN,
    // TOKEN_END

};

class Token
{
public:

    Token()
    : _token(string()), _type(TOKENSTR)
    {}

    Token(string str)
        : _token(str), _type(TOKENSTR)
    {}

    //stk calling this CTOR
    Token(string str, int value)
        : _token(str), _type(TOKENSTR)
    {
        
    }

    virtual string get_token_str() const
    {
        return _token;
    }

    string token_str() const
    {
        return _token;
    }

    virtual void set_token_str(string str)
    {
        _token = str;
    }

    virtual TokenType get_token_type() 
    {
        return _type; //TOKEN
    }

    virtual void set_token_type(TokenType input_type) 
    {
        _type = input_type;
    }

    friend ostream& operator <<(ostream& outs, const Token& t)
    {
        outs << t._token;
        return outs;
    }

private:
    string _token;
    TokenType _type;
};


#endif