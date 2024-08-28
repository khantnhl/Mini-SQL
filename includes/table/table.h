#ifndef TABLE_H
#define TABLE_H

#include "typedefs.h"
#include "../binary_files/file_record.h"
#include "../bplustree/bplustree.h"
#include "../token/resultset.h"
#include "../shuntingyard/shuntingyard.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <stdexcept>

using namespace std;
 
class Table
{
private:
    // Table attributes
    string _filename;
    long _lastrecord;
    static long _serial;

    vectorlong record_history;
    vectorstr _fieldnames;

    map_sl _map;    //field map
    
    vector <mmap_sl> _indices; //keys : value_lists

public:
    //CTORs
    Table();
    Table(const string &filename);
    Table(const string &filename, const vectorstr& fields);

    //no need
    Table& operator=(const Table& RHS)
    {
        if(this != &RHS)
        {
            _filename = RHS._filename;
            _lastrecord = RHS._lastrecord;
            record_history = RHS.record_history;
            _fieldnames = RHS._fieldnames;
            _map = RHS._map;
            _indices = RHS._indices;
        }
        return *this;
    }

    //SELECT FUNCTIONS
    Table select(const vectorstr& fields, const string& field_type, const string& operation, const string &info);
    Table select(const vectorstr &fields, const vectorstr &condition);
    Table select(const vectorstr &fields, Queue<Token *> &token_queue);
    Table select_all(); // returns table

    vectorlong rpn_machine(const vectorstr& fields, Queue<Token*>& token_queue);

    Table vectorstr_to_table(const vectorstr& fields);
    Table vectorlong_to_table(const vectorstr& fields, const vectorlong& rec_numbers);

    vectorlong select_recnos(const string& field_type, const string& operation, const string &info);
    vectorlong select_recnos();

    void setfields(const vectorstr &fields);
    const vectorstr& getfields() const;

    void insert_into(const vectorstr &info);
    void reindex(const vectorstr& fields, long record_num);

    long check_size() const;
    void check_vectorlong(const vectorlong &printme) const;
    void check_vectorstr(const vectorstr &printme) const;
    long get_recordSize();

    friend ostream &operator<<(ostream &outs, const Table &t);
};

long Table::_serial = 0;

Table::Table()
    :  _lastrecord(0), _filename("UNKNOWN")
{}

//CTOR: pass in file
//create a table
Table::Table(const string & filename)
    : _lastrecord(0), _filename(filename)
{
    long num_bytes;

    fstream f;
    FileRecord r;

    //open fields .txt
    open_fileRW(f, (_filename + ".txt").c_str());
    r.read(f, 0);   // read(fstream, long recno)
    f.close();

    //setup index structures of _map with field names
    setfields(r.get_record_vectorstr());

    //initialized my mmap indices with empty mmaps
    for(int i = 0; i < r.get_record_vectorstr().size(); i++)
    {
        _indices.push_back(MMap<string, long>());
    }
    

    //open .bin to store values
    open_fileRW(f, (_filename + ".bin").c_str());

    //golden while loop
    int i = 0;
    num_bytes = r.read(f, i);
    

    while (num_bytes > 0)
    {
        reindex(r.get_record_vectorstr(), i); //inserting fields & rec_nos into respective mmap indices
        i++;
        num_bytes = r.read(f, i);
    }

    _lastrecord = i; //update
    f.close();
}

// pass in filename and fieldnames
// creates blank value .bin file to be inserted
Table::Table(const string & filename, const vectorstr & fields)
    : _filename(filename),  _lastrecord(0)
{
    setfields(fields); //set up _map

    fstream f;
    FileRecord r;
    r = FileRecord(fields); //bucket

    //set up _mmap indices
    for(int i = 0; i < fields.size(); i++)
    {
        _indices.push_back(MMap<string, long>());
    }
    
    open_fileW(f, (filename + ".txt").c_str());
    long recno = r.write(f);

    f.close();

    // open value file
    open_fileW(f, (filename + ".bin").c_str());
    f.close();
}

// pass in fieldnames, field_type, operation, info -> returns Table
Table Table::select(const vectorstr& fields, const string& field_type, const string& operation, const string &info)
{
    _serial++;
    Table t(_filename + to_string(_serial), fields); 

    //select record numbers we need
    vectorlong selected = select_recnos(field_type, operation, info);

    record_history.clear(); //clear past records
    record_history = selected; 

    vectorstr record;
    vectorstr result;


    fstream f; 
    open_fileRW(f, (_filename + ".bin").c_str()); //opens .bin value file
    FileRecord r;

    //loop through record numbers and read the records
    for(int i = 0 ; i < selected.size(); i++)
    {

        r.read(f, selected[i]); //load the bucket

        record = r.get_record_vectorstr();

        //_map[field] = "fname" -> 0
        //record[0] -> Joe
        for(const auto& field : fields)
        {
            result.push_back(record[_map[field]]);
        }

        t.insert_into(result); //insert into table
        result.clear(); //cleared
    }
    
    f.close();
    return t;
}

//work flow
//pass in fields, and string conditions (infix)
//feed in sy ctor an infix string 
// -> ctor convert to infix Token queue -> call postfix()
// -> call select(fields, postfix Token queue) -> returns a table
Table Table::select(const vectorstr &fields, const vectorstr &condition)
{
    Shunting_yard sy(condition);

    Queue<Token*> hold = sy.postfix();

    return select(fields, hold);

}

// Work Flow
// pass in fieldnames, Token_queue (postfix)
// -> feed that queue to rpn_machine
// returns vectorlong -> convert that to table
Table Table::select(const vectorstr& fields, Queue<Token*>& token_queue)
{
    vectorlong selected = rpn_machine(fields, token_queue);

    // check_vectorlong(selected);

    return vectorlong_to_table(fields, selected);
}

// reproduce select_all table
// called on existing table
Table Table::select_all()
{

    return vectorstr_to_table(_fieldnames);
}

// work flow
// convert vectorstr to Table
Table Table::vectorstr_to_table(const vectorstr& fields)
{
    record_history.clear();

    _serial++;

    Table t(_filename + to_string(_serial), fields); //("student" + "1")
    // cout<< _filename;
    // cout<<_serial;

    fstream f;
    FileRecord r;

    // cout << _filename <<endl;

    //open .bin value file
    open_fileRW(f, (_filename + ".bin").c_str());

    //start golden while loop 
    long num_bytes = r.read(f, 0);

    vectorstr hold;
    vectorstr result;

    long track = 0;
    while(num_bytes > 0)
    {
        hold = r.get_record_vectorstr(); //extract string from r bucket 

        // cout<<"hey " << hold <<endl;

        for(const auto& field : fields)
        {
            result.push_back(hold[_map[field]]);
        }

        // cout<< "inserting <<" << result <<endl;

        t.insert_into(result); //insert the record
        
        result.clear();
        record_history.push_back(track);

        track++;
        num_bytes = r.read(f, track);
    }

    // cout<<"here : " <<  record_history <<endl;

    f.close();
    return t;
}

//work flow
// pass in fieldnames, selected record numbers
// calls Table CTOR to setup
// loop through record numbers
// extract string from the bucket and loop through it to insert the full infomation to the .bin
Table Table::vectorlong_to_table(const vectorstr& fields, const vectorlong& rec_numbers)
{

    _serial++;
    Table t((_filename + to_string(_serial)), fields); //set up table

    fstream f; 
    FileRecord r;
    open_fileRW(f, (_filename + ".bin").c_str());

    vectorstr result;

    record_history.clear(); // clear past records
    record_history = rec_numbers;

    //loop through each record number
    for(int i = 0; i < rec_numbers.size(); i++)
    {
        r.read(f, rec_numbers[i]); //load the bucket each time
        
        vectorstr hold = r.get_record_vectorstr(); //extract the vectorstr

        for(const auto& field : fields)
        {
            result.push_back(hold[_map[field]]); //mapping fields with index
        }   

        t.insert_into(result); //insert to table
        result.clear();

    }    

    f.close();
    return t;

}

//work flow
// info -> the data for each person  eg. {"Joe", "Blow", "CS"} -> _indices mmap structures
void Table::insert_into(const vectorstr& info)
{
    fstream f;
    open_fileRW(f, (_filename + ".txt").c_str());
    f.close();

    // eg. (stream, filename) -> employee
    // to value file
    open_fileRW(f, (_filename + ".bin").c_str());

    // record bucket overloaded
    FileRecord re = FileRecord(info);

    // write to file
    long recno = re.write(f); // returns recno
    
    for(int i = 0; i < info.size(); i++)
    {
        _indices[i].insert(info[i], recno);
    }

    f.close();

    _lastrecord++;
}

//SETTER/GETTER
// set_up indices and structures
// eg. fields = {"fname", "lname", "major"}
//set up the _map with keys : values
void Table::setfields(const vectorstr &fields)
{
    for (int i = 0; i < fields.size(); i++)
    {
        _fieldnames.push_back(fields.at(i));
        _map[fields[i]] = i;
        //eg. _map["fname"] = 0  {"fname" : 0}

    }
}

const vectorstr &Table::getfields() const
{
    return _fieldnames;
}

// Work Flow
// input three arguments : field_type, operations (relational sign), record information
// utilizes the power of BPT upper, lower_bounds to know where to start, end, grabbing value_list (record nums) while iterating the leaves
vectorlong Table::select_recnos(const string& field_type, const string& operation, const string &info)
{
    vectorlong hold; 

    if (operation == "=")
    {
        //_indices[_map["age"]].get("17");
        hold = _indices[_map[field_type]].get(info);

    }
    else if (operation == ">")
    {
        for (MMap<string, long>::Iterator it = _indices[_map[field_type]].upper_bound(info); it != _indices[_map[field_type]].end(); it++)
        {
            hold += (*it).value_list;
        }
    }
    else if (operation == "<")
    {
        for (MMap<string, long>::Iterator it = _indices[_map[field_type]].begin(); it != _indices[_map[field_type]].lower_bound(info); it++)
        {

            hold += (*it).value_list;

        }
    }
    else if (operation == "<=")
    {
        for (MMap<string, long>::Iterator it = _indices[_map[field_type]].begin(); it != _indices[_map[field_type]].upper_bound(info); it++)
        {

            hold += (*it).value_list;

        }
    }
    else if (operation == ">=")
    {
        for (MMap<string, long>::Iterator it = _indices[_map[field_type]].lower_bound(info); it != _indices[_map[field_type]].end(); it++)
        {
            hold += (*it).value_list;
        }
    } 
    else if( operation == "all")
    {
        for (MMap<string, long>::Iterator it = _indices[_map[field_type]].begin(); it != _indices[_map[field_type]].end(); it++)
        {
            hold += (*it).value_list;
        }
    }
    else
    {
        cout << "quit cs.";
    }

    return hold;
}

vectorlong Table::select_recnos()
{
    return record_history;
}

// inserting to mmap indices which is a BPT
void Table::reindex(const vectorstr& fields, long record_num)
{
    for (int i = 0; i < fields.size(); i++)
    {
        _indices[i].insert(fields[i], record_num); 
    }
}

//Work Flow
//input fieldnames and Queue_tokens -> returns vectorlong (selected) 
// case RELATIONAL: call select_recnos -> get vector long
// push that to temp stack, for Resultset if logical exists
// case LOGICAL: uses Resultset to either union or intersect, (i tried pointer method)
vectorlong Table::rpn_machine(const vectorstr& fields, Queue<Token*>& token_queue)
    {


        Stack<Token*> stack;
        
        Stack<vectorlong> hold_results;

        vectorlong result, temp1, temp2;

        string operation, field_type, info, logic;
        Token* t_ptr;
        Resultset rs;

        while(!token_queue.empty())
        {
            result.clear(); //clear this vectorlong bucket each round

            Token* hold = token_queue.front();

            switch(hold->get_token_type())
            {
                case TOKENSTR:
                    
                    stack.push(token_queue.pop());
                    break;
                case LPAREN: //doesn't need. just to not get compiler warning 
                    stack.push(token_queue.pop());
                    break;
                case RPAREN: //doesn't need just to not get compiler warning 
                    stack.push(token_queue.pop());
                    break;
                case RELATIONAL: 

                    operation = (token_queue.pop())->get_token_str();

                    info = (stack.pop())->get_token_str();
                    
                    if(stack.empty())
                    {
                        throw std::runtime_error("Missing information to operate relational. ");
                    }

                    field_type = (stack.pop())->get_token_str();

                    if(!stack.empty() && stack.top()->get_token_type() == TOKENSTR) //case where lname Yang major are stacked
                    {
                        throw std::runtime_error("Missing Logical Operator for two relations. ");
                    }

                    result = select_recnos(field_type, operation, info); 
                    hold_results.push(result);

                    break;
                case LOGICAL:

                    if(hold_results.size() < 2)
                    {
                        throw std::runtime_error("Missing informaion for Logical Operation. ");
                    }

                    temp1 = hold_results.pop();
                    check_vectorlong(temp1);
                    temp2 = hold_results.pop();
                    check_vectorlong(temp1);

                    t_ptr = static_cast<Token*>(token_queue.pop());

                    hold_results.push(rs.evaluate(t_ptr, temp1, temp2)->get_resultset_vtrlong());

                    break;
                default:    
                    throw std::runtime_error("RPN error. ");
                    break;
            }


        }

            // cout<<"after stack_s : " << stack.size() <<endl;

            // cout<<"after queue_s : " << token_queue.size() <<endl;
            // cout<< "BUG STACK " <<stack <<endl;

            // assert(token_queue.empty() && "QUEUE IS NOT EMPTY");
            // assert(stack.empty() && "STACK IS NOT EMPTY");
            if(!stack.empty() && !token_queue.empty())
            {
                throw std::runtime_error("RPN machine.");
            }
            
        return hold_results.pop();
    }


//DEBUG PURPOSE
long Table::check_size() const
{
    return _lastrecord;
}

void Table::check_vectorlong(const vectorlong &printme) const
{
    cout << "printing vl{} = ";
    for (auto &x : printme)
    {
        cout << setw(2) << x;
    }

    cout << endl
         << endl;
}

void Table::check_vectorstr(const vectorstr &printme) const
{
    cout << "printing {} = ";
    for (auto &x : printme)
    {
        cout << setw(2) << x;
    }

    cout << endl
         << endl;
}

ostream &operator<<(ostream &outs, const Table &t)
{
    outs << "TableName : " << t._filename << endl;
    outs << "Records: " << t._lastrecord << endl;

    fstream f;

    FileRecord re; // bucket

    // fields file
    open_fileRW(f, (t._filename + ".txt").c_str());

    long label_bytes = re.read(f, 0);
    outs << re << endl; //labels
    f.close();

    // value file
    open_fileRW(f, (t._filename + ".bin").c_str());

    long num_bytes = re.read(f, 0);

    long track_record = 0;
    while (num_bytes > 0)
    {
        // cout<< "bytes check : " << num_bytes <<endl;
        outs << track_record << re << endl;
        track_record++;
        num_bytes = re.read(f, track_record);
    }

    f.close();

    // outs << "here is your map " << t._map <<endl <<endl;
    // outs << "here is your mmap " << t._indices << endl;
    return outs;
}

long Table::get_recordSize()
{
    return _lastrecord;
}

long _serial = 0; 

#endif