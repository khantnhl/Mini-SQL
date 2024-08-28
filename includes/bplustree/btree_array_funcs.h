#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <iostream>
#include <vector>
#include <cassert>
using namespace std; 

template <class T>
T maximal(const T& a, const T& b)
{   
    return max(a,b);
}                     //return the larger of the two items

template <class T>
void swap(T& a, T& b)
{
    T& temp = a;
    a = b; 
    b = temp;
}   
//swap the two items

template <class T>
int index_of_maximal(T data[], int n)
{   
    int sample = data[0];
    int index = 0;
    for(int i = 0; i < n; i++)
    {
        if(data[i] > sample)
        {
            index = i;
        }
    }

    return index;
}                  //return index of the largest item in data

template <class T>
void ordered_insert(T data[], int& n, T entry)
{    
      
}         //insert entry into the sorted array
          //data with length n

//return the first index in data that is not less than entry
template <class T>
int first_ge(const T data[], int n, const T& entry)
{
    int index;
    
    if(n == 0){ return 0; } //if size is 0 return 0;
    
    for(int i = 0; i < n; i++){

        if(data[i] >= entry){
            return i;
        }
    }

    return n;
}    

template <class T>
void attach_item(T data[], int& n, const T& entry)
{

    data[n] = entry;
    n++; //increase size

}     //append entry to the right of data

template <class T>
void insert_item(T data[], int i, int& n, T entry)
{
    n++;

    //i is index
    for(int j = n - 1; j > i; j--){ //out of B taken care
        data[j] = data[j - 1];
    }

    data[i] = entry;  //insert at index
    
}     //insert entry at index i in data


// the last element in data and place it in entry
template <class T>
void detach_item(T data[], int& n, T& entry)
{
    assert(n != 0 && "CANNOT DETACH EMPTY LIST");

    entry = data[n - 1]; //detached the last one, attached to entry but what is entry exactly
    n--;
}           

template <class T>
void delete_item(T data[], int i, int& n, T& entry)
{
    entry = data[i];
    for(int j = i; j < n; j++)
    {
        data[j] = data[j + 1];
    }

    n--; //reduce
}    //delete item at index i and place it in entry


template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)
{
    //call attach()
    
    for(int i = 0; i < n2; i++)
    {
        attach_item(data1, n1, data2[i]);
    }

    n2 = 0; //reset to zero

}    //append data2 to the right of data1
//move n/2 elements from the right of data1
//and move to data2

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)
{
    // n1 - n1/2 --> starting point
    // n1        --> ending point

    for(int i = n1 - n1/2; i < n1; i++)
    {
        data2[n2] = data1[i];
        n2++;
    }
    
    n1 = n1 - n2;

}   

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size)
{
    dest_size = src_size;

    for(int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
    
}   //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1)
{
    if(n == 0){ cout<< "empty|"<<endl; }
    
    for(int i = 0; i < n; i++)
    {
        cout<< data[i] << " |";
    }

}   //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item)
{
    for(int i = 0 ; i < n; i++)
    {
        if(item <= data[i]){ return false; }
    }
    return true;
}        //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item)
{
    for(int i = 0 ; i < n; i++)
    {
        if(item > data[i]){ return false; }
    }
    return true;
}        //item <= all data[i]


//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list)
{
    for(auto it = list.begin(); it != list.end(); it++)
    {
        outs << *it << " ";
    }
    return outs;
}  //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme)
{
    list.push_back(addme);
    return list;
}  //list.push_back addme

template <typename T>
vector<T>& operator +=(vector<T>& list, const vector<T>& addme)
{
    for(int i =0 ; i <  addme.size(); i++)
    {
        list.push_back(addme[i]);
    }
    return list;
} 



#endif
