#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "./bplustree.h"
#include <vector>

//MPair struct for MMap

template < typename K, typename V >
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------

    
    MPair(const K& k = K())
        : key(k)
    {
        //no need to initialize empty vector??
    }

    MPair(const K& k, const V& v)
        : key(k)
    {
        value_list.push_back(v);
    }

    MPair(const K& k, const vector<V>& vlist)
        : key(k), value_list(vlist)
    {}

    //--------------------------------------------------------------------------------

    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << print_me.key << " : " << print_me.value_list;
        return outs;
    }

    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){ return (lhs.key == rhs.key); }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){ return (lhs.key < rhs.key); }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){ return (lhs.key <= rhs.key); }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){ return (lhs.key > rhs.key); }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){ return (lhs.key >= rhs.key); }

    //return type MPair < K, V >
    friend MPair< K, V > operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {   
        MPair<K, V> mpair_result(lhs.key, lhs.value_list);

        for(int i = 0; i < rhs.value_list.size(); i++)
        {
            mpair_result.value_list.push_back(rhs.value_list.at(i));
        }

        return mpair_result; //new mpair object
    }

};


template <typename K, typename V>
class MMap
{

public:

    typedef BPlusTree< MPair <K, V> > map_base; // Public MEMBER! 

    class Iterator{     //can be accessed MMap::Iterator
    public:
        friend class MMap; 

        //ptr CTOR
        Iterator(typename map_base::Iterator it = nullptr)
            : _it(it)
        {}
        
        Iterator operator ++(int unused) //postfix
        {
            Iterator temp = *this;
            _it++;
            return temp;
        }

        Iterator operator ++() //prefix
        {
            _it++;
            return _it;
        }    //pre_increment

        MPair<K, V> operator *()
        {
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){ return(lhs._it == rhs._it); }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){ return(lhs._it != rhs._it); }


    private:
        typename map_base::Iterator _it;
    };


    MMap()
    {
        bool dup = true;
        mmap = BPlusTree< MPair<K, V> > (dup);
    }

    //Iterators
    Iterator begin()
    {
        return mmap.begin();
    }

    Iterator end()
    { 
        return mmap.end(); 
    }

//  Capacity
    int size() const{
        return mmap.size();
    }

    bool empty() const{ return mmap.empty(); }

//  Element Access
    const vector<V>& operator[](const K& key) const
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }

    vector<V>& operator[](const K& key)
    {
        return mmap.get(MPair<K,V>(key)).value_list;
    }

    vector<V>& at(const K& key)
    {
        return mmap.get(MPair<K,V>(key)).value_list;
    }

//  Modifiers
    void insert(const K& k, const V& v){
        mmap.insert(MPair<K, V>(k, v));

    }

    void erase(const K& key){
        mmap.remove(MPair<K,V>(key));
    }

    void clear(){
        mmap.clear_tree();

    }

//  Operations:
    bool contains(const K& key) const { return (mmap.contains(key)); }

    vector<V>& get(const K& key)
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }


    Iterator find(const K& key){
        return Iterator(mmap.find(key));
    }

    int count(const K& key){ return mmap.size(); }


    // I have not writtent hese yet, but we will need them:
    Iterator lower_bound(const K& key)
    {
        return Iterator(mmap.lower_bound(key));
    }

    Iterator upper_bound(const K& key)
    {
        return Iterator(mmap.upper_bound(key));
    }

    // Iterator equal_range(int val)
    // {
    //     return mmap.equal_range(val);
    // }

    bool is_valid(){ return mmap.is_valid(); }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    //debug 
    void print_iter() 
    {
        for(Iterator it= begin(); it != end(); it++)
        {
            cout<<*it << "|";
        }
    }

//multimap function to print mmap as a table
    void print_lookup()
    {
        for(Iterator it = begin(); it != end(); it++)
        {
            if(!(*it).value_list.empty())
                cout<< *it<< endl;
        }
    }

private:

    BPlusTree < MPair <K, V> > mmap; //PRIVATE

};


#endif