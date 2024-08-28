
#include "stokenize.h"
#include "state_machine_functions.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

// Default CTOR
STokenizer::STokenizer()
    : _pos(0)
{

    make_table(_table);
}

//CTOR
STokenizer::STokenizer(char str[])
    : _pos(0)
{
    strcpy(_buffer, str);
    make_table(_table);
}


bool STokenizer::done(){
    return !more();
}            //true: there are no more tokens

bool STokenizer::more(){
        return _pos <= strlen(_buffer);
}            //true: there are more tokens

//set a new string as the input string
void STokenizer::set_string(char str[])
{ 
    strcpy(_buffer, str); //str cpy
    _pos = 0;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    init_table(_table);
}

void STokenizer::_print_table(int _table[][MAX_COLUMNS])
{
    print_table(_table);
}

bool STokenizer::get_token(int& start_state, string& token)
{
    int last_success_pos = -1;
    bool successOccur = false;
    
    for(int i = _pos; i <= strlen(_buffer); i++) 
    {
        char c = _buffer[i];
        start_state = _table[start_state][c];

        if(start_state == -1) //fail 
        {
            break;
        }

        //last case
        if (i == strlen(_buffer) && is_success(_table, start_state)) 
        {
            break;
        }
    
        if (is_success(_table, start_state)) 
        {
            last_success_pos = i;
            successOccur = true;
        }
    }

    if(successOccur && last_success_pos != -1)
    {
        token = string(_buffer + _pos, last_success_pos - _pos + 1);
        _pos = last_success_pos + 1;
    }
    else
    {
        _pos++;
    }

    return !token.empty();
}