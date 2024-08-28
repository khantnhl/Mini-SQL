#ifndef LOGICAL_H
#define LOGICAL_H

class Logical : public Token
{
public: 
    Logical()
    {
        set_token_str(string());
        set_token_type(LOGICAL);
    }
    
    Logical(string s)
    {
        set_token_str(s);
        set_token_type(LOGICAL);
    }

    TokenType get_op_type()
    {
        return LOGICAL;
    }

    

};

#endif