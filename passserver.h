#include "hashtable.h"
#include<string>

//template<>
using namespace cop4530;
using namespace std;
class PassServer: public HashTable<string,string>{
    public:
        PassServer(size_t size=101);
        ~PassServer();
        bool load(const char*filename);
        bool addUser(std::pair<string,string>& kv);
        bool addUser(std::pair<string,string>&& kv);
        bool removeUser(const string & k);
        bool changePassword(const pair<string,string>&p, const string & newpassword);
        bool find(const string & user)const;
        void dump()const;
        size_t size()const;
        bool write_to_file(const char*filename)const;
    private:
        string encrypt(const string& str);
        //HashTable<string,string> ht;
};
#include "passserver.cpp"
