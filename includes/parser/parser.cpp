#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"

Parser::Parser(){
        make_parse_table(cmd_table);
        set_map(keyword_list, map_keys);
}
    
// Setup state machine, multimap, and map
Parser::Parser(char* str)
{   

    strcpy(_pstring, str);

    make_parse_table(cmd_table);
    set_multimap(mmap_labels);
    set_map(keyword_list, map_keys);

    for(int i = 0; i < filteredstr.size(); i++)
    {
        _ptree[filteredstr[i]];
    }

    vectorstr hold = stk_to_vectorstr(_pstring);
    str_to_queue(filteredstr);
    get_parse_tree(input_q);

}
    
// Getter for mmap parsetree
mmap_ss Parser::parse_tree()
{
    return _ptree;
}


// set pstring buffer, tokenize input, filter the tokens, convert to a queue, prepare mmap parse_tree based on State Machine
void Parser::set_string(char s[])
{
    strcpy(_pstring, s);

    stk_to_vectorstr(_pstring);

    
    str_to_queue(filteredstr);
    
    _ptree.clear();
    get_parse_tree(input_q);

}

int Parser::get_column(string& index)
{     
    if(!_keywords.contains(index))
    {
        return SYMBOL; 
    }   
    return _keywords[index];
}

// for example: _keywords["select"] = 1;
void Parser::set_map(const vectorstr& list, const vectorlong& keys)
{
    for(int i = 0; i < list.size(); i++)
    {
        _keywords[list[i]] = keys[i];
    }
}

void Parser::set_multimap(const vectorstr& list)
{
    for(int i = 0; i < list.size(); i++)
    {
        _ptree[list[i]];
    }

}

// Takes in a queue of chopped strings from stk, we will set up the multimap structures total 7 keys, insert into multimap depending on state machine design and states
void Parser::get_parse_tree(Queue<string>& input)
{

    string temp = "yes";

    int start_state = 0;

    while(!input.empty())
    {
        string hold = input.front();

        int column = get_column(hold);
        start_state = cmd_table[start_state][column];

        
        switch(start_state)
        {
            case 1: // commands
                _ptree["command"] += input.pop();
                break;
            case 2: 
                _ptree["fields"] += input.pop();
                break;
            case 3: // table, into, from -> useless
                input.pop(); 
                break;
            case 4: 
                _ptree["table_name"] += input.pop();
                
                break;
            case 5:   // where
                if(column == WHERE)
                {
                    _ptree["where"] += temp; //expected to overwrite "yes"
                } else if(column == SYMBOL)
                {
                    _ptree["condition"] += input.pop();
                    break;
                }
                input.pop();
                break;
            case 6: 
                if(column == SYMBOL)
                {
                    _ptree["values"] += input.pop(); 
                } 
                else {
                    input.pop();
                }
                break;
            case 7:
                if(column == SYMBOL)
                {
                    _ptree["col"] += input.pop();
                } 
                else{
                    input.pop();
                }
                break;
            default:
                flag = false;                    
                throw std::runtime_error("Wrong command line at : " + hold + ". Expected : where/from/tablename. ");
                break;
        }

    }

}

//Parser State Machine 
void Parser::make_parse_table(int _table[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
        {
            cmd_table[i][j] = -1;
        }
    }


    //fail states 0,1,2,3
    mark_fail(_table, 0);   
    mark_fail(_table, 1);            
    mark_fail(_table, 2);             
    mark_fail(_table, 3);             

    //success states 4,5,6,7
    mark_success(_table, 4);
    mark_success(_table, 5);
    mark_success(_table, 6);
    mark_success(_table, 7);

    mark_cells(0, _table, SELECT, 1);   // 0 -> select -> 1 
    mark_cells(0, _table, MAKE, 1);     // 0 -> make -> 1 
    mark_cells(0, _table, INSERT, 1);   // 0 -> insert -> 1 


    mark_cells(1, _table, STAR, 2);     // 1 -> * -> 2
    mark_cells(1, _table, SYMBOL, 2);   // 1 -> symbol -> 2

    mark_cells(1, _table, INTO, 3);     // 1 -> into -> 3
    mark_cells(1, _table, TABLE, 3);    // 1 -> table -> 3

    mark_cells(2, _table, FROM, 3);     //2 -> from -> 3
    mark_cells(2, _table, SYMBOL, 2);   //2 -> symbol -> 2

    mark_cells(3, _table, SYMBOL, 4);   //3 -> symbol -> 4
    mark_cells(4, _table, SYMBOL, 4);   //4 -> symbol -> 4

    mark_cells(4, _table, WHERE, 5);    //4 -> where -> 5
    mark_cells(4, _table, VALUES, 6);   //4 -> values -> 6
    mark_cells(4, _table, FIELDS, 7);   //4 -> fields -> 7

    mark_cells(5, _table, SYMBOL, 5);   //5 -> symbol -> 5

    mark_cells(6, _table, SYMBOL, 6);   //6 -> symbol -> 6

    mark_cells(7, _table, SYMBOL, 7);   // 7 -> symbol -> 7


}

// Get tokens from stk, handles qutoes and trashes returns a polished vector string
vectorstr Parser::stk_to_vectorstr(char s[])
{
    filteredstr.clear();

    STokenizer stk(s);
    Stktoken t;
    stk>>t;

    while(stk.more())
    {
            
        string token = t.token_str();
    
        if(token == "\"")
        {
            string hold; 

            while(stk.more())
            {
                stk>>t;
                token = t.token_str();

                if(token == "\""){ break; }

                hold += token;

            }

            filteredstr.push_back(hold);
            
        } 

        if(!isTrash(t.token_str()) && t.type_string() != "SPACE" && t.token_str() != "\"")
        {
            filteredstr.push_back(t.token_str());
        }

        t = Stktoken();
        stk>>t;
    }

    return filteredstr;
}

// Convert a vectorstr to queue string
Queue<string> Parser::str_to_queue(vectorstr& slist)
{
    for(int i = 0; i < slist.size(); i++)
    {
        input_q.push(slist[i]);
    }
    return input_q;
}

// Utilizes const [] to get rid of unwanted things from the token string
bool Parser::isTrash(const string& s)
{
    for(const char& x : trash)
    {
        if(s[0] == x)
        {
            return true;
        }
    }
    return false;
}

// for debug
void Parser::check_vectorstr(const vectorstr& s)
{
    cout<<endl <<endl;
    cout<<"printing vectorstr{ ";
    for(auto &x : s)
    {

        cout<< setw(2) << x << " ";
    }

    cout<<endl;
}

Map<string, int> Parser::get_keyword_map()
{
    return _keywords;
}

void Parser::print_lookup()
{
    return _ptree.print_lookup();
}

// Getter for bool flag
bool Parser::is_valid()
{
    return flag;
}

#endif