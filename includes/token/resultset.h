#ifndef RESULTSET_H
#define RESULTSET_H
#include "../bplustree/bplustree.h"
#include "logical.h"

#include <algorithm>
#include <iomanip>
#include <stdexcept>

class Resultset : public Token
{
private: 
    vectorlong _recnos;
public: 
    Resultset()
    {}

    Resultset(vectorlong& v1, vectorlong& v2, string& s)
    {   
        _recnos.clear();
        bubble_sort(v1, v1.size());
        bubble_sort(v2, v2.size());

        // sort(v1.begin(), v1.end());
        // sort(v2.begin(), v2.end());

        if(s == "and")
        {
            set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_recnos));
        } 
        if(s == "or") 
        {
            set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_recnos));
        }

    }

    vectorlong and_with_intersect(vectorlong v1, vectorlong v2)
    {

        _recnos.clear();
        bubble_sort(v1, v1.size());
        bubble_sort(v2, v2.size());
        // sort(v1.begin(), v1.end());
        // sort(v2.begin(), v2.end());

        set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_recnos));

        return _recnos;
    } //intersect

    vectorlong or_with_union(vectorlong v1, vectorlong v2){
        
        _recnos.clear();

        bubble_sort(v1, v1.size());
        bubble_sort(v2, v2.size());


        set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(_recnos));

        return _recnos;
    } //union

    vectorlong get_resultset_vtrlong(){
        return _recnos;
    }

    void check_vector(const vectorlong &printme) const
{
    cout << "printing vl{} = ";
    for (auto &x : printme)
    {
        cout << setw(2) << x << " ";
    }

    cout << endl
         << endl;
}


void bubble_sort(vectorlong& list, long size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1;j++)
        {
            if(list[j] > list[j + 1])
            std::swap(list[j], list[j + 1]);
        }
    }
}


    Resultset* evaluate(Token* tptr, vectorlong v1, vectorlong v2)
    {
        string logic;
        _recnos.clear();

        logic = tptr->get_token_str();

        if(logic == "and")
        {
            _recnos = and_with_intersect(v1, v2);
        } else if(logic == "or")
        {
            _recnos = or_with_union(v1, v2);
        }
        else {
            throw std::runtime_error("");
        }

        Resultset* new_rs = new Resultset();
        new_rs->_recnos = _recnos;
        return new_rs;
    }

};

#endif