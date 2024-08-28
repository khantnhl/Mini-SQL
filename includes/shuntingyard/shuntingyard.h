#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H
#include <cassert>
#include <stdexcept>
#include <fstream>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../table/typedefs.h"
#include "../token/tokenstring.h"

class Shunting_yard{
public: 

    Shunting_yard();
    Shunting_yard(const vectorstr& infix_strings);
    Queue<Token*> postfix();

private:

    Queue<Token*> _infix_tqueue; 
    Queue<Token*> _postfix_tqueue;

};

#endif