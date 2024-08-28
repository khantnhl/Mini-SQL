#ifndef MAP_H
#define MAP_H

#include "./bplustree.h"

//Pair struct with map
template <typename K, typename V>
struct Pair{

    K key;
    V value;


    //CTOR
    Pair(const K& k = K(), const V& v = V())
        : key(k), value(v)
    {}

    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "(" << print_me.key << ": " << print_me.value << ")" <<endl;
        return outs;
    }

    //just comparing the keys
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){ return (lhs.key == rhs.key); }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){ return (lhs.key < rhs.key); }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){ return (lhs.key > rhs.key); }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){ return (lhs.key <= rhs.key); }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){ return (lhs.key >= rhs.key); }

    //no need
    //return type Pair < K, V >
    friend Pair< K, V > operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {    
        //do nothing
        return rhs; //just adding the values not key
    }

};
 
template <typename K, typename V> 
class Map
{
public:

    typedef BPlusTree < Pair <K, V> > map_base;  // Pair type BplusTree
    
    class Iterator          //can be accessed Map::Iterator
    {

    public:
        friend class Map;

        //ptr CTOR
        Iterator(typename map_base::Iterator it = NULL)
            : _it(it) 
        {}

        Iterator operator ++(int unused) //postfix
        {
            Iterator temp = _it;
            _it++;
            return temp;
        }

        Iterator operator ++(){
            _it++;
            return _it;
        }

        Pair<K, V> operator *()
        {
            return *_it;
        }

        //compare itrs
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){ return (lhs._it == rhs._it); }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){ return (lhs._it != rhs._it); }

    private:
    
        typename map_base::Iterator _it;    
        //private POINTER encapsulated map_base is a BPlusTree < Pair<K, V> > so _it can be deref key & value

    };

    //CTOR

    Map()
        : key_count(0)
    {}


//  Iterators
    Iterator begin(){ return Iterator(map.begin()); }

    Iterator end(){ return Iterator(map.end()); }

//  Capacity
    int size() const{ return map.size(); }

    bool empty() const{ return map.empty(); }

//  Element Access

    // T& get so T is a Pair for map obj so we just access on the value of it 
    //T& get(const entry) 
    //if it !contains -> insert it
    //else return get_existing
    //thats why when we index the map it's inserted on the BplusTree
    V& operator[](const K& key)
    {
        return at(key); 
    }

    V& at(const K& key)
    {
        return map.get(Pair<K, V>(key)).value; //this calls the T& get(T& entry)
    }
    
    const V& at(const K& key) const
    {
        return map.get(Pair<K, V>(key)).value;  //this calls the const T& get(const T& entry) const
    }


//  Modifiers
    void insert(const K& k, const V& v){ 
        map.insert(Pair<K,V>(k,v)); 
        key_count++;
    }
    
    void erase(const K& key){ 
        map.remove(Pair<K,V>(key)); 
        key_count--;
    }

    void clear(){ 
        map.clear_tree(); 
        key_count = 0;
    }

    V get(const K& key)
    {
        return map.get(Pair<K,V>(key)).value;
    }

//  Operations:
    Iterator find(const K& key)
    {
        return Iterator(map.find(Pair<K,V>(key)));
    }

    bool contains(const Pair<K, V>& target) const{ 
        return map.contains(Pair<K,V>(target));
    }

    // I have not writtent these yet, but we will need them:
    int count(const K& key){ return key_count; }


    //stops if key is equal or smaller
    //return end() if not found
    Iterator lower_bound(const K& key){ 
        return map.lower_bound(key);
    }

    Iterator upper_bound(const K& key){ 
        return map.upper_bound(key);
    }
    
    // Iterator equal_range(){ return map.equal_range(Pair<K, V>(key)); }

    bool is_valid(){ return map.is_valid(); }

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:

    int key_count;
    BPlusTree< Pair <K, V> > map; //MAP CLASS -> map private which is B+TREE

};


#endif