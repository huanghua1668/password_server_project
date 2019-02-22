#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<fstream>

namespace cop4530{
    // max_prime is used by the helpful functions provided
    // to you.
    static const unsigned int max_prime = 1301081;
    // the default_capacity is used if the initial capacity 
    // of the underlying vector of the hash table is zero. 
    static const unsigned int default_capacity = 11;

    template <typename K, typename V>
    class HashTable{
        public:
            HashTable(size_t size=101);
            ~HashTable();
            bool contains(const K& k) const;
            bool match(const std::pair<K,V>& kv) const;
            bool insert(const std::pair<K,V>& kv);
            bool insert(const std::pair<K,V>&& kv);
            bool remove(const K& k);
            void clear();
            bool load(const char*filename);
            void dump() const;
            bool write_to_file(const char* filename) const;
            size_t size()const;
        
        private:
            void makeEmpty();
            void rehash();
            size_t myhash(const K&k) const;
            unsigned long prime_below (unsigned long n);
            void setPrimes(std::vector<unsigned long>& vprimes);
            std::vector<std::list<std::pair<K,V>>>theLists;
            size_t currentSize;
    };
    #include"hashtable.hpp"
}
#endif
