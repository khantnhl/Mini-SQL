#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
using namespace std;

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "()?.,:;'`~!*\\\"";
const char OPERATORS[] = "><=!+-%&|";
const char trash[] = "?.,:;'`~!";

const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;

//token types:
const int TOKEN_NUMBER = 1; //DIGITS
const int TOKEN_ALPHA = 2;  //ALFA
const int TOKEN_SPACE = 3;  //SPACE
const int TOKEN_PUNC = 5;   //PUNC
const int TOKEN_UNKNOWN = -1; //UNKNOWN

const int TOKEN_OPERATOR = 4;
const int TOKEN_END = -2;


enum keys {SELECT = 1, STAR, FROM, WHERE, COND, FIELDS, INSERT, INTO, MAKE, TABLE, SYMBOL, VALUES};


#endif