#ifndef STOKENIZE_H
#define STOKENIZE_H

#include "stktoken.h"
#include "state_machine_functions.h"

#include<assert.h>
using namespace std;

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
     
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Stktoken& t)
    {
        string token; //this will be the extracted word

        int i = 0;

        if(s.get_token(i , token)){ //if get_token is true, generates and gets a stoken

            //t= Token(token, s._table[0][token[0]]);
            t = Stktoken(token, get_type(token, s._table));
            return s;
        } 
        return s;
    }
    
    //set a new string as the input string
    void set_string(char str[]);

    void _print_table(int _table[][MAX_COLUMNS]);
    

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int& start_state, string& token);
    
    //bool get_token(string& input, int pos, int state, int table[][MAX_COLUMNS], string& t);

    //---------------------------------
    char _buffer[MAX_BUFFER];        //input char string
    int _pos;                       //current position in the string
    
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif