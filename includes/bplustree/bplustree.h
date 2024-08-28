#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "./btree_array_funcs.h"
#include <iomanip>

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;

        // ITER CTOR
        Iterator(BPlusTree<T>* _it = nullptr, int _key_ptr = 0)
            : it(_it), key_ptr(_key_ptr){}

        T operator *()
        {
            return it->data[key_ptr]; // dereference by indexing T data
        }

        Iterator operator++(int un_used) //post-fix increment
        {

            assert(it);

            //hold
            Iterator temp = *this;

            if(key_ptr < it->data_count - 1)
            {

                key_ptr++; //increment

            } else {
                //if ptr goes out of bounds
                it = it->next; //move pointer
                key_ptr = 0; //reset

            }

            return temp;
        }

        Iterator operator++() //pre-fix operator
        {

            assert(it);

            //return type Iterator

            if(key_ptr < it->data_count - 1) 
            {
                key_ptr++;
            } else {
                //out of b

                it = it->next; //move next
                key_ptr = 0; //reset

            }

            return *this;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr);
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.it != rhs.it) || (lhs.key_ptr != rhs.key_ptr);
        }

        void print_Iterator(){
            if(it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }

        bool is_null(){ return !it; }

        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:

        BPlusTree<T>* it;  //pointer
        int key_ptr;    //value //index for data
    
    };

    BPlusTree(bool dups = false){
        data_count = 0;
        child_count = 0;
        next = nullptr;
        dups_ok = dups;
    }

    BPlusTree(T *a, int size, bool dups = false)
        : data_count(0), child_count(0), next(nullptr), dups_ok(dups)
    {
        for(int i = 0; i < size; i++)
        {
            insert(a[i]);
        }
    }

    //big three:

    //COPY CTOR
    BPlusTree(const BPlusTree<T>& other)
    {
        dups_ok = other.dups_ok; //even necessary? 

        copy_tree(other);
    }

    //DESTRUCTOR
    ~BPlusTree()
    {
        clear_tree();
    }

    //ASSIGNMENT
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS)
    {
        if(this != &RHS)
        {
            clear_tree();
            dups_ok = RHS.dups_ok;
            copy_tree(RHS);
        }
        return *this; //return deref *pointer
    }
//------------------------------------------------

    void copy_tree(const BPlusTree<T>& other)
    {

        BPlusTree<T>* last_node_ptr = nullptr; 
        copy_tree(other, last_node_ptr);

    }  

    //pass in BPlusTree pointer
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
    {
        copy_array(this->data, other.data, this->data_count, other.data_count); //copy the data

        child_count = other.child_count;
        dups_ok = other.dups_ok;
        
        //check if src is a leaf
        if(other.is_leaf())
        {

            if(last_node == nullptr) //if it is nullptr, first time 1encounter leaf
            {
                last_node = this; //first leaf...last node points to me

            }
            else {
                
                last_node->next = this; //last node->next points to me->next which is nullptr.
                
                last_node = this; //move the ptr

            }
            
            
        }

        
        if(child_count > 0)
        {
            for(int i = 0; i < child_count; i++)
            {
                // create new BPlustree node
                subset[i] = new BPlusTree<T>(dups_ok);

                // evoke copy on subsets
                subset[i]->copy_tree(*other.subset[i], last_node); 
            }
        }

    }

    void insert(const T& entry)
    {
        loose_insert(entry);

        // Grow tree
        if(data_count > MAXIMUM)
        {
            //1. create new Btree obj
            BPlusTree* new_node = new BPlusTree<T>(dups_ok);

            //2. copy data
            //3. copy children
            copy_array(new_node->data, this->data, new_node->data_count, this->data_count); 
            copy_array(new_node->subset, this->subset, new_node->child_count, this->child_count);

            //4. dc to 0, cc to 1
            data_count = 0;     //root
            child_count = 1;    //single child

            //5. assign it to subset[0]
            subset[0] = new_node;

            fix_excess(0);
        }   

    }   //insert entry into the tree

    void remove(const T& entry)
    {
        loose_remove(entry);

        if(data_count < MINIMUM && child_count == MINIMUM)
        {

            //shrink tree;
            BPlusTree* shrink_ptr;
            shrink_ptr = subset[0];

            copy_array(data, shrink_ptr->data, data_count, shrink_ptr->data_count);
            copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);

            shrink_ptr->data_count= 0;
            shrink_ptr->child_count= 0;

            delete shrink_ptr;

        }
    }  //remove entry from the tree

    void clear_tree()
    {
        if(!is_leaf())
        {
            for(int i = 0; i < child_count; i++)
            {
                subset[i]->clear_tree();
                delete subset[i];
                subset[i] = nullptr;
            }
        }

        data_count = 0;
        child_count = 0;


    }  //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const{

        int index = first_ge(data, data_count, entry);
        
        bool found  = false;

        if(data[index] == entry && index < data_count)
        {
            found = true;
        }

        if(found)
        {   
            if(is_leaf()){ //return true if only found at leaf
                return true;
            } else { return subset[index + 1]->contains(entry); }  //index + 1 because we added the item to the leftmost of the right subtree
        } else 
        {   
            if(is_leaf())
            {
                return false;
            }

            return subset[index]->contains(entry);
        }        
    } //true if entry can be found

    T& get(const T& entry)
    {

        if(!contains(entry))
        {
            insert(entry);
        }

        return get_existing(entry);
    }              // return a reference to entry

    //const funct get
    const T& get(const T& entry)const
    {

        int index = first_ge(data, data_count, entry);

        bool found = (index < data_count && data[index] == entry);
    
        if(found)
        {
            if(is_leaf())
            {
                return data[index]; // returning item
            } else {

                return subset[index + 1]->get(entry); // in the breadcrumbs, we found but not leaf so we traverse right 
            }
        } else {
            if(is_leaf())
            {
                return nullptr; // check again
            } else 
            {
                subset[index]->get(entry);
            }
        }
    }   // return a reference to entry

    T& get_existing(const T& entry)
    {
        int index = first_ge(data, data_count, entry);

        bool found = (index < data_count && data[index] == entry);

        if(is_leaf())
        {
            if(found)
            { 
                return data[index]; // returning item
            } else 
            {
                assert(found && "get_existing was called with nonexistent entry");
                exit(2);
            }
        } else {
            if(found)
                return subset[index + 1]->get(entry); // if found and is not leaf -> find in inner nodes
            return subset[index]->get(entry);
        
        }
    }     // return a reference to entry


    Iterator find(const T& key)
    {
        int index = first_ge(data, data_count, key);

        bool found = (index < data_count && data[index] == key);

        if(found)
        {
            if(is_leaf())
            {
                return Iterator(this, index);
            } else {
                return subset[index + 1]->find(key); // in breadcrumbs
            }
        } else {
            if(is_leaf())
            {
                return Iterator(nullptr); // it is a leaf and you don't found it so return Iterator type null 
            } else {
                return subset[index]->find(key);
            }
        }
    }         // return an iterator to this key.
              // NULL if not there.
    

    Iterator lower_bound(const T& key)
    {
        int index = first_ge(data, data_count, key);

        bool found = (index < data_count && data[index] == key); 


        if(is_leaf())
        {   
            for(Iterator it = begin(); it != end(); it++)
            {
                 if(key <= *it)
                {
                    return it;
                }
                
            }
            return Iterator(nullptr);
        }
        else 
        {
            if(found)
            {
                return subset[index + 1]->lower_bound(key);
            } else 
            {
                return subset[index]->lower_bound(key);
            }
        }
        
    }  
 
    //exist or not, the next entry  > entry
    Iterator upper_bound(const T& key)
    {
        int index = first_ge(data, data_count, key);

        bool found = (index < data_count && data[index] == key); 

        if(is_leaf())
        {
            for(Iterator it = begin(); it != end(); it++)
            {
                 if(key < *it)
                {
                    return it;
                }
            }
            return Iterator(nullptr);
        } else 
        {
            if(found)
            {
                return  subset[index + 1]->upper_bound(key);
            } else 
            {
                return subset[index]->upper_bound(key);
            }
        }
    }   


    int size() const
    {
        int total = data_count;

        for(int i =0; i < child_count; i++)
        {
            total += subset[i]->size();
        }

        return total;
    }                    //count the number of elements

    bool empty() const { return (data_count==0 && child_count==0); }                  //true if the tree is empty

    void print_tree(int level = 0, ostream &outs=cout) const
    {   
        if(!is_leaf())
        {
            subset[child_count - 1]->print_tree(level + 1); //traverse rightmost
        }

        if(next){ cout<< setw(4 * level) << " " << "^\n"; }

        cout<< setw(4 * level) << " " << "⎴\n";
        for(int i = data_count - 1; i >= 0; i--)
        {   
            cout<< setw(4 * level) << " " << data[i] <<endl;

            if(!is_leaf()){
                subset[i]->print_tree(level + 1);
            }
        }
        cout<< setw(4 * level) << " " <<"⎵\n";


    }
    
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    // incomplete
    bool is_valid(){ 
        if(is_leaf()){ return true; }
        
        for(int i = 0; i < data_count; i++)
        {
            if(data[data_count - 1] > subset[data_count]->data[i])
            {
                return false;
            }
        }

        
        for(int i = 0; i < data_count; i++)
        {
            if(!contains(data[i])){ return false; }
        }
        

        return true; 
    }

    //left, root, right
    string in_order()
    {
        string str;

        if(!is_leaf())
        {
            str += subset[0]->in_order(); //left
        }
        for(int i = 0; i < data_count; i++)
        {
            str += to_string(data[i]) + "|"; //root

            if(!is_leaf())
            {
                str += subset[i + 1]->in_order(); //right
            }
        }

        return str;
    }

    //root, left, right
    string pre_order()
    {
        string str;
        
        for(int i = 0; i < data_count; i++)
        {
            str += to_string(data[i]) + "|"; //root


            if(!is_leaf())
            {
                str += subset[i]->pre_order(); //left subtree
            }
        }
        
        if(!is_leaf())
        {
            str += subset[data_count]->pre_order(); //right subtree
        }

        return str;
    }
    
    //left, right, root
    string post_order()
    {

     string str;

        if(!is_leaf())
        {
            str += subset[0]->post_order(); //left
        }

        for(int i = 0; i < data_count; i++)
        {

            if(!is_leaf())
            {
                str += subset[i + 1]->post_order(); //right
            }
            str += to_string(data[i]) + "|"; //root

        }

        return str;
    }
    
    string post_secondary_testing()
    {   
        string str;

        if(!is_leaf())
        {
            str += subset[0]->post_secondary();
        }

        for(int i = 0; i < data_count; i++)
        {

            if(!is_leaf())
            {
                str += subset[i + 1]->post_secondary();
            }
            str += to_string(data[i]) + "|";

        }

        return str;

    }

    Iterator begin()
    {
        return Iterator(get_smallest_node());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

    void make_tree()
    {

        data[0] = 75;

        subset[0] = new BPlusTree<T>();
        subset[1] = new BPlusTree<T>();

        data_count = 1;
        child_count = 2;

//ptrs //level 1
        BPlusTree<T>* p = subset[0];

        BPlusTree<T>* p1 = subset[1];


        p->data[0] = 50;

        p->data_count = 1;
        
        p->child_count = 2;

        p1->data[0] = 120;
        p1->data_count = 1;
        p1->child_count = 2;

//level 2
        p->subset[0] = new BPlusTree<T>();
        BPlusTree<T>* subp = p->subset[0];
        subp->data[0] = 35;
        subp->data_count = 1;
        subp->child_count = 2;

        p->subset[1] = new BPlusTree<T>();
        BPlusTree<T>* subp1 = p->subset[1];
        subp1->data[0] = 60;
        subp1->data_count = 1;
        subp1->child_count = 2;

// level 2 right subtree 

        p1->subset[0] = new BPlusTree<T>();
        BPlusTree<T>* subp01 = p1->subset[0];
        subp01->data[0] = 90;
        subp01->data[1] = 100;
        subp01->data_count = 2;
        subp01->child_count = 3;

        p1->subset[1] = new BPlusTree<T>();
        BPlusTree<T>* subp02 = p1->subset[1];
        subp02->data[0] = 180;
        subp02->data[1] = 200;
        subp02->data_count = 2;
        subp02->child_count = 3;

// level 3
    //left subtree
    subp->subset[0] = new BPlusTree<T>();
    BPlusTree<T>* subp03 = subp->subset[0];
    subp03->data[0] = 10;
    subp03->data[1] = 25;
    subp03->data_count = 2;
    subp03->child_count = 0;

    subp->subset[1] = new BPlusTree<T>();
    BPlusTree<T>* subp13 = subp->subset[1];
    subp13->data[0] = 35;
    subp13->data_count = 1;
    subp13->child_count = 0;
        
    subp1->subset[0] = new BPlusTree<T>();
    BPlusTree<T>* subp_l03 = subp1->subset[0];
    subp_l03->data[0] = 50;
    subp_l03->data[1] = 55;
    subp_l03->data_count = 2;
    subp_l03->child_count = 0;

    subp1->subset[1] = new BPlusTree<T>();
    BPlusTree<T>* subp_l13 = subp1->subset[1];
    subp_l13->data[0] = 60;
    subp_l13->data_count = 1;
    subp_l13->child_count = 0;

    // right subtree
    subp01->subset[0] = new BPlusTree<T>();
    BPlusTree<T>* subp_r03 =  subp01->subset[0];
    subp_r03->data[0] = 75;
    subp_r03->data[1] = 80;
    subp_r03->data_count = 2;
    subp_r03->child_count = 0;

    subp01->subset[1] = new BPlusTree<T>();
    BPlusTree<T>* subp_r13 =  subp01->subset[1];
    subp_r13->data[0] = 90;
    subp_r13->data[1] = 95;
    subp_r13->data_count = 2;
    subp_r13->child_count = 0;
 
    subp01->subset[2] = new BPlusTree<T>();
    BPlusTree<T>* subp_r23 =  subp01->subset[2];
    subp_r23->data[0] = 100;
    subp_r23->data_count = 1;
    subp_r23->child_count = 0;

    subp02->subset[0] = new BPlusTree<T>();
    BPlusTree<T>* subpr02 = subp02->subset[0];
    subpr02->data[0] = 120;
    subpr02->data[1] = 150;
    subpr02->data_count = 2;
    subpr02->child_count = 0;

    subp02->subset[1] = new BPlusTree<T>();
    BPlusTree<T>* subpr12 = subp02->subset[1];
    subpr12->data[0] = 180;
    subpr12->data[1] = 190;
    subpr12->data_count = 2;
    subpr12->child_count = 0;

    subp02->subset[2] = new BPlusTree<T>();
    BPlusTree<T>* subpr22 = subp02->subset[2];
    subpr22->data[0] = 200;
    subpr22->data[1] = 210;
    subpr22->data_count = 2;
    subpr22->child_count = 0;
    }

    T& smallest_item(T& entry)
    {
        get_smallest(entry);
        return entry;
    }
    
    T& biggest_item(T& entry)
    {
        get_biggest(entry);
        return entry;
    }

  //for DEBUGGING
    BPlusTree<T>* smallest_node()
    {
        return get_smallest_node();
    }
   
    BPlusTree<T>* biggest_node()
    {
        return get_biggest_node();
    }

    BPlusTree<T>* next_node()
    {
        return next;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    int child_count;                     //number of children

    T data[MAXIMUM + 1];                 //holds the keys
    BPlusTree* subset[MAXIMUM + 2];      //subtrees

    BPlusTree* next;
    
    bool is_leaf() const{ return (child_count == 0); }             //true if this is a leaf node

    T* find_ptr(const T& entry)
    {
        int index;
        bool found = false;

        index = first_ge(data, data_count, entry);

        if(data[index] == entry && index < data_count)
        { found = true; }

        if(found)
        {
            if(is_leaf())
            {
                return &data[index]; 
            } else {
                return subset[index + 1]->find(entry);
            }
        }
        else {
            if(is_leaf()){ 
                return nullptr;
            }
            return subset[index]->find(entry); //if not, go down til leaf
        }
    }

    //return a pointer to this key.
    // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry)
    {
        int index = first_ge(data, data_count, entry); 
        bool found = false;

        if(data[index] == entry && index < data_count)
        { found = true; }

        if(found)
        {
            if(is_leaf()){
                if(dups_ok)
                {

                    //is a duplicate
                    data[index] = data[index] + entry; 
                } else 
                {
                    data[index] = entry;
                }
                
            } else {
                // in the breadcrumbs, if not leaf -> traverse subset[index + 1]
                subset[index + 1]->loose_insert(entry);
                if(subset[index + 1]->data_count > MAXIMUM)
                {
                    fix_excess(index);
                }
            }
        } 
        else {
            if(is_leaf())
            {
                insert_item(data, index, data_count, entry); 
            } else {
                subset[index]->loose_insert(entry);
                if(subset[index]->data_count > MAXIMUM)
                {
                    fix_excess(index);
                }
            }
        }

    }   
    
    // allows MAXIMUM + 1 data elements in
    // the root
    
    void fix_excess(int i)
    {
        //1. create new BTree obj
        BPlusTree<T>* new_node = new BPlusTree<T>(dups_ok);

        //2. split the array, data & subsets
        split(subset[i]->data, subset[i]->data_count, new_node->data, new_node->data_count);
        split(subset[i]->subset, subset[i]->child_count, new_node->subset, new_node->child_count);

        //3. detach from subset[i]
        T temp;
        detach_item(subset[i]->data, subset[i]->data_count,  temp); //detach last item from first original subset

        //4. insert it to top, bringing it up
        insert_item(data, i , data_count, temp); //transfer up 

        //5. link the new_node into subset[i + 1]
        insert_item(subset, i + 1, child_count, new_node); //link new node into subset[i + 1] 

        //in BpT, 
        //if it is a leaf, insert it to the front of subset[i + 1], like making a copy of it in leftmost of right subtree
        if(subset[i]->is_leaf())
        {
            insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp); //insert middle item to pos 0 of subset[i + 1]

            // connect the links
            subset[i + 1]->next = subset[i]->next; // whatever subset[i]->next was** pointing to

            subset[i]->next = subset[i + 1]; // then link

        }
    }
    // fix excess in child i

// remove element functions:
    void loose_remove(const T& entry)
    {
        int index = first_ge(data, data_count, entry);

        bool found = (index < data_count && data[index] == entry);

        T temp; 

        if(found)
        {
            if(is_leaf())
            {   
                // a. found, so we just delete it
                delete_item(data, index, data_count, temp);
            } else 
            {
                // b. found but not leaf, so subset[index + 1]
                subset[index + 1]->loose_remove(entry);

                // in breadcrumbs
                if(subset[index + 1]->data_count < MINIMUM)
                {
                    cout<<"SHORTAGE...\n";

                    // needs to be replaced by current smallest key

                    fix_shortage(index + 1);

                    // after fix_shortage(i + 1)

                    // search for entry in data -> if found, replace with smallest

                    // else search in subset[i]->data and replace
                }
            }
        } else 
        {
            if(is_leaf())
            {
                // c. not found and it is leaf ->nothing to do
                cout<<"item not found, nothing to do";
                return;
            } else 
            {
                // d. not found and is not leaf
                // search in next level
                
                subset[index]->loose_remove(entry);
                if(subset[index]->data_count < MINIMUM)
                {
                    cout << " SHORTAGE...\n ";
                    fix_shortage(index);
                }
            }
        }
    }  // allows MINIMUM-1 data elements
                                        // in the root

    BPlusTree<T>* fix_shortage(int i)
    {

        if((i < child_count -1)   && subset[i + 1]->data_count > MINIMUM)
        {
            //prioritize (borrow from right)
            //1. transfer left
            transfer_left(i + 1);
            return subset[i];

        } else if ((i > 0)  && subset[i - 1]->data_count > MINIMUM)
        {
            //2. transfer right
            transfer_right(i - 1); //fixed at i but called at (i - 1) left subset
            return subset[i];

        } else if(subset[i - 1] && (i < child_count - 1)){        // prioritize (merge with right) first
            // merge_with_next_subset(i - 1);      // fixed at i
            return subset[i];

        } else {       
            // merge_with_next_subset(i);      // fixed at i
            return subset[i];
        }
    }  //fix shortage in child i

    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node()
    {
        if(!is_leaf())
        { 
            return subset[0]->get_smallest_node(); 
        } //traverse leftmost
        return this;//this is leftmost leaf 
    }

    BPlusTree<T>* get_biggest_node()
    {
        if(!is_leaf())
        { 
            return subset[data_count]->get_biggest_node(); 
        } // traverse leftmost
        return this; // this is leftmost leaf 
    }

    void get_smallest(T& entry)
    {
        if(!is_leaf()){ subset[0]->get_smallest(entry); }
        else 
        {
            entry = data[0]; // indexing smallest 
        }
    }     // entry := leftmost leaf

    void get_biggest(T& entry)
    {
        if(!is_leaf()){ subset[data_count]->get_biggest(entry); } 
        else {
            entry = data[data_count - 1];
        }
    }       // entry := rightmost leaf

    void remove_biggest(T& entry)
    {
        if(!is_leaf())
        { 
            subset[child_count - 1]->remove_biggest(entry);  // can also do subset[data_count]

            if(subset[data_count]->data_count < MINIMUM)
            {
                fix_shortage(child_count - 1);
                return;
            }
        }
        else
        {
            detach_item(data, data_count, entry);
        };
    }    // remove the biggest child of tree->entry


    void transfer_left(int i)
    {}     // transfer one element LEFT from child i

    // calling at subset(i + 1) but actually fixing for subset(i) //incomplete full of bugs // doesn't work
    void transfer_right(int i)
    {
        T top;
        T lower;

        BPlusTree* minor_child = nullptr; // special case
        
        //----------BTREE PART----------------//
        
        // from top
        delete_item(data, i, data_count, top);
        cout<< "top: " <<top <<endl;

        // from back of left subset
        delete_item(subset[i]->data, subset[i]->data_count - 1, subset[i]->data_count, lower); 


        // bring that up to data
        insert_item(data, i , data_count, top);

        // attach to right subset
        attach_item(subset[i + 1]->data, subset[i + 1]->data_count, lower);

//-------------BTREE PART-----------------//

        // if is leaf -> we have to replace with subset[i + 1]->data[0] after borrowing the key
        if(subset[i + 1]->is_leaf())
        {
            data[i] = subset[i + 1]->data[0]; // replace
        } else 
        {   
       
            delete_item(subset[i + 1]->subset, 0 , subset[i + 1]->child_count, minor_child); 
            
            //attach
            attach_item(subset[i]->subset, subset[i]->child_count, minor_child);
        }
    }       //transfer one element RIGHT from child i

    
    BPlusTree<T>* merge_with_next_subset(int i)
    {

        T top;

        //1. detach() top item
        delete_item(data, i , data_count, top);

        //2. attach() 
        attach_item(subset[i]->data, subset[i]->data_count, top);

        //3. merge subset i with subset i + 1
        merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);

        //merge subset
        merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);


        BPlusTree<T>* loose_subtree = subset[i + 1];
        delete loose_subtree;

        child_count--;
                
        return subset[i];
    }
};  


#endif