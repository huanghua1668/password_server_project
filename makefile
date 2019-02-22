all: sproj5.x proj5.x
sproj5.x: sproj5.o
	g++ -lcrypt -o sproj5.x sproj5.o 
proj5.x: proj5.o
	g++ -lcrypt -o proj5.x proj5.o 
sproj5.o: sproj5.cpp hashtable.h hashtable.hpp passserver.h passserver.cpp
	g++ -std=c++11 -lcrypt -c sproj5.cpp
proj5.o: proj5.cpp hashtable.h hashtable.hpp passserver.h passserver.cpp
	g++ -std=c++11 -lcrypt -c proj5.cpp
clear: *.o proj5.x sproj5.x
	rm *.o proj5.x sproj5.x

