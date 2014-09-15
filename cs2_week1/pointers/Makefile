all : exploit64

clean :
	rm -f exploit64 exploit32 exploit.o

exploit64 : exploit.o
	g++ -o exploit64 exploit.o blackbox.o.64
	
exploit32 : exploit.o
	g++ -o exploit32 exploit.o blackbox.o.32
    
exploit.o :
	g++ -c -g -Wall --std=c++0x -o exploit.o exploit.cpp
