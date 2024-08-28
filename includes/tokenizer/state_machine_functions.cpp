#ifndef STATE_MACHINE_FUNCTIONS_CPP
#define STATE_MACHINE_FUNCTIONS_CPP

#include "state_machine_functions.h"
#include "constants.h"

//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }

    // Mark states 0,2 as fail states
    mark_fail(_table, 0);            
    mark_fail(_table, 2);             

    // Mark states 1,3,4,5,6,7,8 as success states
    mark_success(_table, 1);
    mark_success(_table, 3);        
    mark_success(_table, 4);
    mark_success(_table, 5);
    mark_success(_table, 6);
    mark_success(_table, 7);
    mark_success(_table, 8);

    //ALPHA //3
    mark_cells(0, _table, ALFA, 3);  //state[0] - ALPHA --> [3]
    mark_cells(3, _table, ALFA, 3);
    

    //PUNC  //4
    mark_cells(0, _table, PUNC, 4);     //row [0]  mark "PUNC" --> [4]

    //DIGIT //1
    mark_cells(0, _table, DIGITS, 1);    //state :  row[0] --- DIGITS ---> [1]
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]

    mark_cells(2, _table, DIGITS, 6);    //state [2] --- DIGITS ---> [6]
    mark_cells(6, _table, DIGITS, 6);    //state [6] --- DIGITS ---> [6]
    mark_cells(7, _table, DIGITS, 6);
    
    //SPACES //5
    mark_cells(0, _table, SPACES, 5); 
    mark_cells(5, _table, SPACES, 5); 


    //OPERATOR //8
    mark_cells(0, _table, OPERATORS, 8);
    mark_cells(8, _table, OPERATORS, 8); 

    mark_cell(0, _table, '.', 7);  //state [0] --- '.' ------> [7]
    mark_cell(1, _table, '.', 2);  //state [1] --- '.' ------> [2] 




}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    return _table[state][0] == 1;
}

//Mark a range of cells  in the array. 
//i assume cells mean columns
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{   
    for(int i = from ; i <= to ; i++)
    {
        _table[row][i] = state; //the columns
    }
}

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{   
    int i=0;
    while(columns[i] != '\0')
    {
        _table[row][columns[i]] = state;
        i++;
    }
}

void mark_cells(int row, int _table[][MAX_COLUMNS], keys col, int state)
{   

    _table[row][col] = state;
    
}

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state)
{
    table[row][column] = state;
}

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
        {
                cout << " |" << _table[i][j] << "| ";
        }
        cout <<endl
            <<endl;
    }
}


//show string s and mark this position on the string:
//hello world   pos: 7
//       ^

void show_string(char s[], int _pos)
{
    cout<<s <<endl; //print 
    for(int i = 0; i < _pos; i++){ //pos 0...6
        cout<< " ";
    }
    cout<< "^" <<endl; //pos 7
}

int get_type(string str, int table[][MAX_COLUMNS])
{
//str is a token
    return table[0][str[0]]; 
}

#endif