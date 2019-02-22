//#include<iostream>
//#include<vector>
#include<algorithm>

using namespace std;
using namespace cop4530;
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size){
    theLists.resize(prime_below(size));
    currentSize=0;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable(){
    clear();
}

template <typename K, typename V>
size_t HashTable<K, V>::size()const{
    return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const{
    auto whichList=theLists[myhash(k)];
    for(auto itr=whichList.begin();itr!=whichList.end();++itr)
        if(itr->first==k) return true;
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>:: match(const std::pair<K,V>& kv) const{
    auto whichList=theLists[myhash(kv.first)];
    if(whichList.size()==0)return false;
    for(auto itr=whichList.begin(); itr!=whichList.end();++itr){
        if(itr->first==kv.first)
            return itr->second==kv.second;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V>& kv){
    if(match(kv))return false;
    auto& whichList=theLists[myhash(kv.first)];
    if(contains(kv.first)){
        for(auto itr=whichList.begin(); itr!=whichList.end();++itr){
            if(itr->first==kv.first)
                itr->second=kv.second;
                return true;
        }
    }
    else{
        whichList.emplace(whichList.begin(),kv.first,kv.second);
        if(++currentSize>theLists.size())rehash();
        return true;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V>&& kv){
    if(match(kv))return false;
    auto& whichList=theLists[myhash(kv.first)];
    if(contains(kv.first)){
        for(auto itr=whichList.begin(); itr!=whichList.end();++itr){
            if(itr->first==kv.first)
                *itr=std::move(kv);
                return true;
        }
    }
    else{
        //whichList.insert(whichList.begin(),std::move(kv.first),std::move(kv.second));
        whichList.emplace(whichList.begin(),std::move(kv.first),std::move(kv.second));
        if(++currentSize>theLists.size())rehash();
        return true;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k){
    if(!contains(k))return false;
    auto& whichList=theLists[myhash(k)];
    for(auto itr=whichList.begin();itr!=whichList.end();++itr){
        if(itr->first==k){
            whichList.erase(itr);
            break;
        }
    }
    currentSize--;
    return true;
}

template <typename K, typename V>
void HashTable<K, V>::clear(){
    makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char*filename){
    ifstream myfile(filename);
    K key;
    V value;
    if(myfile.is_open()){
        while(!myfile.eof()){
            myfile>>key>>value;
            std::pair<K,V> thisPair=std::make_pair(key,value);
            insert(std::make_pair(key,value));
            //insert(thisPair);
        }
        return true;
    }
    else
        return false;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const{
    for(int i=0;i<theLists.size();i++){
        std::cout<<"v["<<i<<"]:";
        if(theLists[i].size()>0){
            auto itr=theLists[i].begin();
            std::cout<<' '<<itr->first<<' '<<itr->second;
            ++itr;
            for(;itr!=theLists[i].end();++itr)
                std::cout<<":"<<itr->first<<' '<<itr->second;
            std::cout<<std::endl;
        }
        else
        std::cout<<std::endl;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const{
    ofstream myfile(filename);
    if(myfile.is_open()){
        for(int i=0;i<theLists.size();i++){
            for (auto whichPair:theLists[i])
                myfile<<whichPair.first<<' '<<whichPair.second<<std::endl;
        }
        return true;
    }
    else return false;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty(){
    for(auto & thisList:theLists)
        thisList.clear();
}

template <typename K, typename V>
void HashTable<K, V>::rehash(){
    std::vector<std::list<std::pair<K,V>>> oldLists=theLists;
    theLists.resize(prime_below (2*theLists.size()));
    for(auto& thisList:theLists)
        thisList.clear();
    currentSize=0;
    for(auto& thisList:oldLists)
        for(auto& thisPair:thisList)
            insert(std::move(thisPair));
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K&k) const{
    static std::hash<K> hf;
    return hf(k)%theLists.size();
}
