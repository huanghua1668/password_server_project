#include "hashtable.h"
#include<string>
#include<crypt.h>

PassServer::PassServer(size_t size):HashTable<string,string>(size){
    //HashTable<string,string>::HashTable(size);
    //can not call constructor directly
}

PassServer::~PassServer(){
     //ht.~HashTable();
}

bool PassServer::load(const char*filename){
     return HashTable<string,string>::load(filename);
}

bool PassServer::addUser(std::pair<string,string>& kv){
    string v=encrypt(kv.second);
    return HashTable<string,string>::insert(std::make_pair(kv.first,v));
}

bool PassServer::addUser(std::pair<string,string>&& kv){
    string v=encrypt(std::move(kv.second));
    return HashTable<string,string>::insert(std::make_pair(std::move(kv.first),v));
}

bool PassServer::removeUser(const string & k){
    return HashTable<string,string>::remove(k);
}

bool PassServer::changePassword(const pair<string,string>&p, const string & newpassword){
    string vOld=encrypt(p.second);
    string key=p.first;
    auto oldPair=std::make_pair(key,vOld);
    if(!HashTable<string,string>::match(oldPair))
        return false;
    if(p.second==newpassword)return false;
    removeUser(key);
    return addUser(std::make_pair(key,newpassword));
}

bool PassServer::find(const string & user)const{
    return HashTable<string,string>::contains(user);
}

void PassServer::dump()const{
    HashTable<string,string>::dump();
}

size_t PassServer::size()const{
    return HashTable<string,string>::size();
}

bool PassServer::write_to_file(const char*filename)const{
    return HashTable<string,string>::write_to_file(filename);
}

string PassServer::encrypt(const string& str){
    char salt[]="$1$########";
    string pwdOrigin=crypt(str.c_str(),salt);
    return pwdOrigin.substr(12,22);
}

