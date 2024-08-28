#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
using namespace std;
#include "assert.h"
#include "../node/node.h"


//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head)
{
    for(node<T>* walker = head; walker != nullptr; walker = walker->_next)
    {
        cout << "<-["<< walker->_item << "]->";  //print the item
    }
    cout<< "|||"<<endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{   
    //base case
    if(head->_next == nullptr) {
        cout<<"<-[" << head->_item << "]->";    //print the last node in the list
    } else { 
        _print_list_backwards(head->_next); //recursive calls
        cout<<"<-[" << head->_item << "]->";
    }
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                                T key)
{
    for(node<T>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if(walker->_item == key)
            return walker;        //returning reference
    }
    return nullptr;    //null if it is not found
}


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this)
{
    node<T>* newNode = new node<T>(insert_this, head);

    if(head != nullptr) 
    {
        head->_prev = newNode;  //if the head is not nullptr then connect _prev link
    }

    head = newNode;
    return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this)
{
    if(head == nullptr) //if the list is empty
    {
        return _insert_head(head, insert_this);
    } else 
    {
        assert((after_this != nullptr) && "Target doesn't exist in list");

        node<T>* newNode = new node<T>(insert_this);
        
        newNode->_next = after_this->_next;  //link->
        after_this->_next = newNode; //link->
        
        newNode->_prev = after_this;    //securing _prev links
        if(newNode->_next != nullptr) //if the next of new node is not nullptr
        {
            newNode->_next->_prev = newNode;    
        }
        return newNode; // the inserted node
    }
    return nullptr;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this)
{
    if(head == nullptr) //if the list is empty
    {
        return _insert_head(head, insert_this);
    }
    else if(before_this == head) {  //if before_this is head
        return _insert_head(head, insert_this);
    } else 
    {
        assert(before_this != nullptr && "Target is not in list");

        node<T>* newNode = new node<T>(insert_this);
        node<T>* temp = _previous_node(before_this); //get pointer to prev node

        newNode->_next = before_this; //link->
        temp->_next = newNode; //link->
        
        //securing _prev links
        before_this->_prev = newNode;
        newNode->_prev = temp;
        return newNode; // the inserted node
    }
    return nullptr; //if before_this is the not in the list
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this)
{
    if(prev_to_this == nullptr) //if node is not in the list
        return nullptr;
    return prev_to_this->_prev; 
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this)
{
    T temp;
    assert(delete_this != nullptr && "delete_this is nullptr");

    if(delete_this == head) //case when delete_this is the head
    {
        temp = head->_item;
        head = head->_next;
    }
    else { 
        node<T>* prev = _previous_node(delete_this);    //get pointer to previous node
        temp = delete_this->_item; //store _item before we delete

        //securing _prev links
        prev->_next = delete_this->_next;

        if(delete_this->_next != nullptr)  
        {
            delete_this->_next->_prev = prev;        
        }
    }
    
    delete delete_this;
    return temp;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head)
{
    if(head != nullptr)
    {
        node<T>* newNode = new node<T>(head->_item);
        node<T>* new_walker = newNode; 

        //walker = head->next so we don't double copy the head
        for(node<T>* walker = head->_next; walker != nullptr; walker = walker->_next)
        {
            new_walker = _insert_after(newNode, new_walker, walker->_item); 
        }
        return newNode; //return pointer to newNode(head)
    }
    return nullptr;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    if(src == nullptr) 
    {
        dest = nullptr; //**destination set to null if the src is empty 
        return nullptr;
    }

    dest = new node<T>(src->_item);
    node<T>* new_walker = dest; //point to destination

    //src->next so we don't double copy the head
    for(node<T>* walker = src->_next; walker != nullptr; walker = walker->_next)
    {
        _insert_after(dest, new_walker, walker->_item);
        new_walker = new_walker->_next;


    }
    return new_walker; //last_node
}


// delete all the nodes
template <typename T>
void _clear_list(node<T>*& head)
{
    while(head != nullptr)
    {
        node<T>* hold = head;
        head = head->_next;    //move the head first
        delete hold;    //delete the head 
    }
    head = nullptr;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos)
{
    assert(pos >= 0);

    int i=0;
    for(node<T>* walker = head; walker != nullptr; walker = walker->_next)
    {
        if(i == pos) //serve like array index
        {
            return walker->_item;
        }
        i++;
    }
    return head->_item; //if the head, doesn't exit
}

#endif 