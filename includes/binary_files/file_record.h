#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>
#include "utilities.h"

using namespace std;

void confuse_me();
//----------------------------------------------------------------------------
//                      C L A S S   R E C O R D
//----------------------------------------------------------------------------


class FileRecord{
private:
    static const int MAX = 100;

    int recno; // not using this in the entire program 
    int _num_of_fields; 

    char _record[MAX + 1][MAX + 1]; //static array

public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    FileRecord()
        : recno(-1), _num_of_fields(0)
    {
        
        for(int i = 0; i < MAX; i++)
        {
            _record[i][0] = '\0';
        }
    
    }

    // pass in char string
    FileRecord(char str[])
        : recno(-1)    
    {
        strncpy(_record[0], str, MAX);
    
    }

    // pass in string
    FileRecord(string& s)
        : recno(-1)
    {

        strncpy(_record[0], s.c_str(), MAX);
    }

    // pass in string type vector 
    FileRecord(const vector<string>& fields)
        : recno(-1)
    {
        
        for(int i = 0; i < fields.size(); i ++)
        {
            strncpy(_record[i], fields.at(i).c_str(), MAX);
        }

        _record[fields.size()][0] = '\0';
        // need to manually append null char at the end
    }

    long write(fstream& outs);              //returns the record number

    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file

    vector<string> get_record_vectorstr();

    friend ostream& operator<<(ostream& outs,
                               const FileRecord& r);


};

/// @brief r.write(f); take the Record r and write it into file f
/// @param outs 
/// @return  return the record number of this Record

long FileRecord::write(fstream &outs){
    
    //write to the end of the file.
    outs.seekg(0, outs.end);


    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    //outs.write(&record[0], sizeof(record));
    outs.write(&_record[0][0], sizeof(_record));

    // cout<< "pos [" << pos << "]"<< endl;
    // cout<< "sizeof() : " << sizeof(_record) <<endl;
    // cout<< "current pos: " << pos/sizeof(_record) <<endl;

    return pos/sizeof(_record);  //record number
}


/// @brief 
/// @param ins 
/// @param recno 
/// @return returns the number of bytes read.
long FileRecord::read(fstream &ins, long recno){
    
    long pos = recno * sizeof(_record);


    ins.seekg(pos, ios_base::beg);
    
    ins.read(&_record[0][0], sizeof(_record));

    _num_of_fields = 0;
    
    int i = 0;
    while(_record[i][0] != '\0')
    {   
        i++;
        _num_of_fields++;
    }
    return ins.gcount();

}

// eg. pushed infos -> {"Joe", "Gomez", "CS}
vector<string> FileRecord::get_record_vectorstr()
{
    vector<string> hold;

    for(int i = 0; i < _num_of_fields; i++)
    {
        hold.push_back(string(_record[i]));

    }
    return hold;
}

ostream& operator<<(ostream& outs,
                    const FileRecord& r){

    int i = 0;
    
    while(r._record[i][0] != '\0')
    {   
        outs<<setw(20) << r._record[i];
        i++;
    }
    return outs;
}


void confuse_me(){
    string list[10] = {"zero",
                       "one",
                       "two",
                       "three",
                       "four",
                       "five",
                       "six",
                       "seven",
                       "eight",
                       "nine"};

    cout << "[ ]Show the list of input records:" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout<<setw(6)<<list[i];
    }
    cout << endl<<endl;

    cout << "[ ]Write / INSERT records into the file:" << endl;
    cout << "--------------------------------------------" << endl;


    fstream f;
    //reset the file:
    open_fileW(f, "record_list.bin");
    for (int i= 0; i<10; i++){
        FileRecord r(list[i]);      //filling the envelop
        long recno = r.write(f);
        cout<<"["<<setw(5)<<list[i] <<"]"<< " was written into file as record: "<<setw(2)<<recno<<endl;
    }
    f.close();
    cout << endl
          << endl;

    cout << "[ ]Read / RETRIEVE / SELECT records from the file: " << endl;
    cout << "------------------------------------------------------" << endl;

    FileRecord r;
    int selected_records[] = {4,6,8,9};
    // open the file for reading and writing.
    open_fileRW(f, "record_list.bin" );
    for (int i = 0; i < 4; i++){
        r.read(f, i);
        cout << "reading record " << i << ": " << r << endl;
    }

    cout << "\n\n[ ]Reading passed the end of file: " << endl;
    cout << "---------------------------------------------" << endl;

    long bytes = r.read(f, 19);
    cout<<"  number of bytes read: "<<bytes<<endl;

}

#endif