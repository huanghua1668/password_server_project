#include"passserver.h"
#include<iostream>
#include<crypt.h>
#include<termios.h>
#include<unistd.h>

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
    //for masking password input
    //refer to http://www.cplusplus.com/forum/beginner/43683/
    termios oldt;
    tcgetattr(STDIN_FILENO,&oldt);
    termios newt=oldt;
    newt.c_lflag&=~ECHO;
    do{
        Menu();
        std::cin>>ch;
        string name,pwd;
        string pwdNew;
        char* filename=new char[34];
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
                tcsetattr(STDIN_FILENO,TCSANOW,&newt);
                std::cin>>pwd;
                //recover when finish inputing pwd
                tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
                if(ps.addUser(std::make_pair(name,pwd)))
                    std::cout<<"\nUser "<<name<<" added\n";
                else
                    std::cout<<"\n*****Error: User already exits. Could not add user.\n ";
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
                tcsetattr(STDIN_FILENO,TCSANOW,&newt);
                std::cin>>pwd;
                tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
                std::cout<<"\nEnter new password: ";
                tcsetattr(STDIN_FILENO,TCSANOW,&newt);
                std::cin>>pwdNew;
                tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
                if(ps.changePassword(std::make_pair(name,pwd),pwdNew))
                    std::cout<<"\nPassword changed for user "<<name<<std::endl;
                else
                    std::cout<<"\n*****Error: Could not change user password\n";
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
    return 0;
}

