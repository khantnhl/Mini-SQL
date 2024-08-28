#ifndef SQL_H
#define SQL_H

#include "../table/table.h"
#include "../parser/parser.h"

#include <string>
#include <cassert>
#include <fstream>

using namespace std;

class SQL
{
private: 

    char _sql_buffer[MAX_BUFFER];
    Table _table;
    Map<string, Table> _table_list; //to store table objs, only save when user make a new table
    bool _flag;

public:
    
    SQL(){};

    //pass in command line, parser parse the string and set up parse tree multimap using Parser state machine
    Table command(const string& str){
        string filename;

        vectorstr filenamelist, fields, col, values, condition_list, commands;
        fstream f;

        strcpy(_sql_buffer, str.c_str());
        Parser parser(_sql_buffer);

        mmap_ss ptree;
        Map<string, int> _map;
        ptree = parser.parse_tree(); //bring out the mmap from parser

        /* disable here to see the mmap */

        // ptree.print_lookup(); 

        _map = parser.get_keyword_map(); //bring out the map


        // Value_lists
        commands = ptree["commands"];
        filenamelist = ptree["table_name"]; 
        fields = ptree["fields"];
        values = ptree["values"];
        col = ptree["col"];
        condition_list = ptree["condition"];

        // if input is nothing
        if(filenamelist.empty() || (filenamelist.empty() && fields.empty() && values.empty() && col.empty() && condition_list.empty())){
            throw std::runtime_error("No file name(table). ");
        } 

        if(ptree["where"].size() != 0 && condition_list.size() == 0)
        {
            throw std::runtime_error("Incomplete command. Need Conditions. ");
        }

        filename = filenamelist[0];
        
        FileRecord f_record = FileRecord(filename); //bucket

        string cmd_string;
        cmd_string = ptree["command"].at(0);        

        int cmd_key = _map[cmd_string];
        
        

        switch(cmd_key)
        {
            case MAKE:

                _table = Table(filename, col);

                f.open("file_list.txt", std::fstream::in | std::fstream::out);
            
                f << filename <<endl;

                f.close();
                
                break; 
            case INSERT:

                _table.insert_into(values);
                
                _table_list[filename] = _table; // save it into map


                break;
            case SELECT:

                _table = Table(filename);

                if(fields[0] == "*" && condition_list.size() == 0) // no condition and * case
                {
                    cout<< "There is no condition.\n";
                    Table t = _table.select_all();

                    return t;

                } else if ((fields.size() >= 1) && condition_list.size() == 0){ // no condition but there are fields
                    
                    cout<< "There is no condition.\n";
                    
                    Table t = _table.vectorstr_to_table(fields);
                    
                    return t;

                } else if((fields[0] != "*") && condition_list.size() != 0) { // there is a condition and chosen fields
                    
                    cout<< "There is condition and chosen fields.\n";
                    Table t = _table.select(fields, condition_list);
                    
                    return t;

                }else {
                    cout<<"with conditions\n"; 
                
                    vectorstr field_labels = _table.getfields();
                    Table t = _table.select(field_labels, condition_list);
                    return t;

                } 
            default: 

                throw std::runtime_error("Error : " + cmd_string + "." + "Expected: select, insert into, make table" +  "\n");
                return _table;
        }
        
        return _table;
    }

vectorlong select_recnos()
{
    return _table.select_recnos();
}


void run()
{
    string input;
    
    cout<< "\t--------RUN SQL DATABASE--------\t\n";

    do
    {   
        cout<<endl;
        cout<< ">>> "; getline(cin, input);

        try
        {
            cout<< command(input);
            cout << "records selected: "<<select_recnos() << endl;

        } catch (std::exception& e)
        {
            cout<< "Invalid: " << e.what();
            cout<< "Please Try Again." <<endl;
        }

    } while(input != "e");


}

Map<string, Table> get_map()
{
    cout<<"Tables we are managing ...\n";
    return _table_list;
}

Table access_via_map(const string& findme)
{
    assert(_table_list.contains(findme)); //filename must exist 
    return _table_list[findme];
}


void batch(const vector<string>& command_list)
{
    int j = 1;

    for(int i = 0; i < command_list.size(); i++)
    {   
        cout << j << ". "<< command_list[i] <<endl;
        try
        {
            cout<< command(command_list[i]);
            cout << "records selected: "<<select_recnos() << endl <<endl;

        } catch (std::exception& e)
        {
            cout<< "Invalid command: " << e.what();
            cout<< "Please try again." <<endl;
        }

        j++;
        cout<<endl<<endl;
    }

    cout<< "Table we are managing..." << endl;
    cout<< _table_list;
}

vector<string> batch(const string& filename)
{
    fstream f;
    vector<string>batch_commands;

    f.open(filename);

    if(!f.is_open())
    {
        throw std::runtime_error("file doesn't open.");
    } else 
    {
        string str;
        while(getline(f, str))
        {
            batch_commands.push_back(str);
        }
    }

    f.close();
    return batch_commands;
}

};

#endif