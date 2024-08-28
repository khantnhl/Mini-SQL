#include "stktoken.h"

Stktoken::Stktoken()
    : _token(string()), _type(-1)
{

}

Stktoken::Stktoken(string str, int type)
    : _token(str), _type(type)
{

}

string Stktoken::type_string() const
{
    switch(_type) 
    {
        case 1 :  
            return string("NUMBER");
        case 3 :  
            return string("ALPHA");
        case 5 : 
            return string("SPACE");
        case 4 :   
            return string("PUNC");
        case 7: 
            return string("PUNC");
        case 8:
            return string("OPERATOR");
        case 2 : 
            return string("PUNC");
        default :  //UNKNOWN, -1
            return string("UNKNOWN");
    } 
}

ostream& operator <<(ostream& outs, const Stktoken& t)
{
    outs << t._token <<endl;
    return outs;
}

int Stktoken::type() const
{
    return _type;
}



string Stktoken::token_str() const
{
    return _token;
}