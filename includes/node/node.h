#ifndef NODE_H
#define NODE_H

using namespace std;
#include <iostream>

template <class T>
struct node
{
    T _item;
    node<T>* _next;
    node<T>* _prev;

    node(const T& item, node<T>* next = nullptr, node<T>* prev = nullptr)
    :   _item(item), _next(next), _prev(prev)   //initializer list
    {
    }

    friend ostream& operator <<(ostream& outs, const node<T>& print_me)
    {
    outs<<"<-["<<print_me._item<<"]->";
    return outs;
    }

};

#endif