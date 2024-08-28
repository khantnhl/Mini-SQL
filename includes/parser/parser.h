#ifndef PARSER_H
#define PARSER_H

#include "../tokenizer/constants.h"
#include "../tokenizer/stokenize.h"
#include "../table/typedefs.h"
#include "../queue/MyQueue.h"

#include <cstring>
#include <iomanip>
#include <stdexcept>

class Parser {
public: 
    Parser();
    Parser(char* str);
    
    mmap_ss parse_tree();

    void set_string(char s[]);

    int get_column(string& index);

    void set_map(const vectorstr& list, const vectorlong& keys);
    
    void set_multimap(const vectorstr& list);

    void get_parse_tree(Queue<string>& input);

    //Parser State Machine 
    void make_parse_table(int _table[][MAX_COLUMNS]);

    vectorstr stk_to_vectorstr(char s[]);

    Queue<string> str_to_queue(vectorstr& slist);

    bool isTrash(const string& s);

    
    void check_vectorstr(const vectorstr& s);

    Map<string, int> get_keyword_map();

    void print_lookup();

    bool is_valid();

private: 
    char _pstring[MAX_BUFFER]; //internal buffer

    mmap_ss _ptree; //_mmap
    Map<string, int> _keywords; //_map
    bool flag = true;

    vectorstr filteredstr;
    Queue<string> input_q;

    int cmd_table[MAX_ROWS][MAX_COLUMNS];

    //for mmap 
    vectorstr mmap_labels = {"command", "table_name", "fields", "col", "where", "condition"};

    //for map
    vectorstr keyword_list = {"select", "*", "from", "where", "values","fields", "insert", "into", "make", "table"};
    
    vectorlong map_keys = {SELECT, STAR, FROM, WHERE, VALUES, FIELDS, INSERT, INTO, MAKE, TABLE};

};

#endif