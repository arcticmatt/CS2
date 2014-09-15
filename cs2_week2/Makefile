CC = g++
LD = g++
CPPFLAGS = -std=c++0x -g -Wall -pedantic
LDFLAGS = 

all: sorter fileio list convexhull

list:
	$(CC) $(CPPFLAGS) linked_list.cpp -o linked_list

sorter: sorter.cpp fileio.cpp sorter.h fileio.h
	$(CC) $(CPPFLAGS) fileio.cpp sorter.cpp -o sorter

fileio: testFileIO.cpp fileio.cpp fileio.h
	$(CC) $(CPPFLAGS) testFileIO.cpp fileio.cpp -o testFileIO

convexhull: ConvexHullApp.cpp ConvexHullApp.h HullAlgorithms.cpp structs.h HullAlgorithms.h
	$(CC) $(CPPFLAGS) `sdl-config --cflags` ConvexHullApp.cpp HullAlgorithms.cpp `sdl-config --libs` -lSDL_gfx -o ConvexHullApp

clean :
	rm -rf angleSort argcv sorter fileio linked_list ConvexHullApp testFileIO *.o *.dSYM
