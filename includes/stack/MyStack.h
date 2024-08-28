#ifndef MYSTACK_H
#define MYSTACK_H

#include<iostream>
using namespace std;
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr

        Iterator(){_ptr = NULL;}            //default ctor

        Iterator(node<ITEM_TYPE>* p)
        {
            _ptr = p;
        }      //Point Iterator to where
                //  p is pointing to

        ITEM_TYPE operator *()
        {
            return _ptr->_item;
        }    //dereference operator

        bool is_null()
        {return _ptr == NULL;}            //true if _ptr is NULL

        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){                        //member operator:++it
            _ptr = _ptr->_next; //increment first by moving the pointer
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){        //friend operator: it++
            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();

    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe);
    Iterator begin() const;                  //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

//constructor
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack()
    : _top(nullptr), _size(0){} //initializer list

//copy constructor
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe)
    : _size(copyMe._size) 
{
    _copy_list(_top, copyMe._top);
}

//Destructor
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    _clear_list(_top);
}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS)
{
    if(this != & RHS)    //if RHS not same with obj
    {
        //_clear_list(_top);
        _copy_list(_top, RHS._top);
        _size = RHS._size;
    }    
    return *this;
}

template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    assert(!empty());
    return _top->_item;
}

template<typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){return _size==0;}

template<typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _insert_head(_top, item);
    _size++;
}

template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    if(empty())
        throw runtime_error("Stack is empty can't pop.");
    ITEM_TYPE temp = _top->_item;
    _delete_node(_top, _top);
    _size--;
    return temp;
}

template<typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    return Iterator(_top);
}                   //Iterator to the head node

template<typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const
{
    return Iterator(nullptr);
}                     //Iterator to NULL

template<typename ITEM_TYPE>
ostream& operator<<(ostream& outs, const Stack<ITEM_TYPE>& printMe)
{
    for(typename Stack<ITEM_TYPE>::Iterator it = printMe.begin(); it != printMe.end(); it++) 
    {
        outs<<"["<< **it <<"]->";
    }
    cout<< "|||";
    return outs;
}

#endif