#ifndef MYQUEUE_H
#define MYQUEUE_H

#include<iostream>
#include "assert.h"

using namespace std;
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue; //give access to list to access _ptr

        Iterator()
        {
            _ptr = NULL;
        }   //default ctor

        Iterator(node<T>* p)
        {
            _ptr = p;
        }                           //Point Iterator to where
                                    //  p is pointing to

        T operator *()
        {
            return _ptr->_item;
        }    //dereference operator

        bool is_null(){
            return _ptr == NULL;
        }            //true if _ptr is NULL

        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }


        Iterator& operator++(){                         //member operator:++it
                                                        // or ++it = new_value
            _ptr = _ptr->_next; //move the ptr
            return *this; //return the obj ref
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){         //friend operator: it++
            Iterator temp = it; //store first
            it._ptr = (it._ptr)->_next; //increment
            return temp;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();
    Queue(const Queue<T>& copyMe);
    ~Queue();

    Queue& operator=(const Queue<T>& RHS);
    bool empty();
    T front();
    T back();
    void push(T item);
    T pop();
    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;                    //Iterator to NULL
    void print_pointers();
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
    int size() const { return _size; }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

//constructor
template<typename T>
Queue<T>::Queue()
    : _front(nullptr), _rear(nullptr), _size(0) {} //initializer list

//copy constructor
template<typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _front = nullptr; 
    //_clear_list(_front);
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template<typename T>
Queue<T>::~Queue()      //Destructor
{
    _clear_list(_front);
}

//asignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if(this != & RHS) //if not same with the obj
    {
        _rear = _copy_list(_front, RHS._front); //_rear and _front assigned
        _size = RHS._size;
    }
    return *this;
}

template<typename T>
bool Queue<T>::empty()
{
    return _size == 0;
}

template<typename T>
T Queue<T>::front()
{
    if(empty())
        throw invalid_argument("Queue is empty");
    return _front->_item;
}

template<typename T>
T Queue<T>::back()
{
    if(empty())
        throw invalid_argument("Queue is empty");
    return _rear->_item;
}

template<typename T>
void Queue<T>::push(T item)
{
    //if stack is empty
    if(_size == 0){
        _front = _insert_head(_front, item);
        _rear = _front;  //update rear
    } else {    
        _rear = _insert_after(_front, _rear, item); //append it to the rear if stack is not empty
    }
    _size++;
}

template<typename T>
T Queue<T>::pop()
{
    if(empty())
        throw invalid_argument("Queue is empty");
    T temp = _front->_item;
    _delete_node(_front,_front); 
    _size--;
    return temp;
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
    //return typename Queue<T>::Iterator(_front);
}            //Iterator to the head node

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(nullptr);
    //or return typename Queue<T>::Iterator(nullptr);

}                   //Iterator to NULL

template<typename T>
void Queue<T>::print_pointers()
{
    cout<< "front: " << front() <<endl;
    cout<< "rear: " << back() <<endl;
}

template<typename T>
ostream& operator << (ostream& outs, const Queue<T>& printMe)
{
    for(typename Queue<T>::Iterator it = printMe.begin(); it != printMe.end(); it++)
    {
        outs<< "["<< *it << "]->";
    }
    outs<< "|||";
    return outs;
}

template<typename T>
ostream& operator << (ostream& outs, const Queue<T*>& printMe)
{
    for(typename Queue<T*>::Iterator it = printMe.begin(); it != printMe.end(); it++)
    {
        outs<< "["<< **it << "]->";
    }
    outs<< "|||";
    return outs;
}
#endif