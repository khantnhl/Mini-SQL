#include <iostream>
#include <iomanip>
#include <vector>

#include "includes/sql/sql.h"

using namespace std;

const vector<string> make_command_list = {
    //---- employee table ----------//

    "make table employee fields  last, first, dep, salary, year",
    "insert into employee values Blow, Joe, CS, 100000, 2018",
    "insert into employee values Blow, JoAnn, Physics, 200000, 2016",
    "insert into employee values Johnson, Jack, HR, 150000, 2014",
    "insert into employee values Johnson, \"Jimmy\" ,Chemistry,140000, 2018",

    //----- student table ----------//
    "make table student fields fname, lname, major, age, company",
    "insert into student values Flo, Yao, CS, 20, Google",
    "insert into student values Bo, Yang, CS, 28, Microsoft",
    "insert into student values \"Sammuel L.\", Jackson, CS, 40, Uber",
    "insert into student values \"Flo\", \"Jackson\", Math, 21, Google",
    "insert into student values \"Greg\", \"Pearson\", Physics, 20, Amazon"

};

const vector<string> select_command_list = {

// Testing edge cases and exceptions

/*1 valid*/      "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*2 comma*/     "select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*3 field name*/     "select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*4 from */     "select lname, fname, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*5 table name*/     "select lname, fname, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*6 condition*/     "select lname, fname, major from student where",
/*7 missing left paren*/     "select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson",
/*8 missing right paren*/     "select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson",
/*9 need more info*/     "select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson",

/*10 valid */     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",

/*11 need logical operator*/    "select lname, fname, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson",

/*12 need more info*/     "select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson",
/*13 need more info*/     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or ",
/*14 valid */     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",

};

int main(int argv, char** argc) {

    SQL sql;
    sql.run();

    //run sql batches for testing edge cases
    // sql.batch(make_command_list);
    // sql.batch(select_command_list);


    cout << "\n\n\n=====================" << endl;
    return 0;
}
