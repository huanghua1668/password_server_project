#include"passserver.h"
#include<iostream>
#include<crypt.h>
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main(){
    size_t size;
    std::cout<<"Enter preferred hash table capacity: ";
    std::cin>>size;
    PassServer ps(size);
    char ch;
    char* filename=new char[34];
    do{
        Menu();
        std::cin>>ch;
        string name,pwd;
        string pwdNew;
        switch(ch){
            case 'l':
                std::cout<<"Enter password file name to load from: ";
                std::cin>>filename;
                if(!ps.load(filename))std::cout<<"Cannot open file "<<filename<<std::endl;
                break;
            case 'a':
                std::cout<<"Enter username: ";
                std::cin>>name;
                std::cout<<"Enter password: ";
                std::cin>>pwd;
                if(ps.addUser(std::make_pair(name,pwd)))
                    std::cout<<"User "<<name<<" added\n";
                else
                    std::cout<<"*****Error: User already exits. Could not add user.\n ";
                break;
            case 'r':
                std::cout<<"Enter username: ";
                std::cin>>name;
                if(!ps.removeUser(name))
                    std::cout<<"*****Error: User not found. Could not delete user"<<std::endl;
                else
                    std::cout<<"User "<<name<<" deleted\n";
                break;
            case 'c':
                std::cout<<"Enter username: ";
                std::cin>>name;
                std::cout<<"Enter password: ";
                std::cin>>pwd;
                std::cout<<"Enter new password: ";
                std::cin>>pwdNew;
                if(ps.changePassword(std::make_pair(name,pwd),pwdNew))
                    std::cout<<"Password changed for user "<<name<<std::endl;
                else
                    std::cout<<"*****Error: Could not change user password\n";
                break;
            case 'f':
                std::cout<<"Enter username: ";
                std::cin>>name;
                if(ps.find(name))
                    std::cout<<"User "<<name<<" found."<<std::endl;
                else
                    std::cout<<"User "<<name<<" not found."<<std::endl;
                break;
            case 'd':
                ps.dump();
                break;
            case 's':
                std::cout<<"Size of hashtable: "<<ps.size()<<std::endl;
                break;
            case 'w':
                std::cout<<"Enter password file name to write to: ";
                std::cin>>filename;
                if(!ps.write_to_file(filename)) 
                    std::cout<<"*****Error: Could not write to file "<<filename<<std::endl;
                break;
            case 'x':
                break;
        }
    }while(ch!='x');
    delete filename;
    return 0;
}

