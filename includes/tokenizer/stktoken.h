#ifndef Stktoken_H
#define Stktoken_H

#include "constants.h"
#include<iostream>
#include<string>

using namespace std; 

class Stktoken
{

public:
    Stktoken();
    Stktoken(string str, int type);
    friend ostream& operator <<(ostream& outs, const Stktoken& t);
    int type() const;
    
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
 
};

#endif