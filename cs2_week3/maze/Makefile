CC = g++
DOCSGEN = doxygen
CFLAGS = -Wall -ansi -pedantic -ggdb `sdl-config --cflags`
LIBS = `sdl-config --libs` -lSDL_gfx
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCSDIR = docs
OBJS = $(OBJDIR)/MazeSolverApp.o $(OBJDIR)/RecursiveBacktracker.o \
	$(OBJDIR)/MazeGrid.o $(OBJDIR)/BreadthFirstSolver.o \
	$(OBJDIR)/CoordinateQueue.o $(OBJDIR)/DepthFirstSolver.o \
	$(OBJDIR)/CoordinateStack.o

.PHONY: maze testsuite clean docs

maze: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(BINDIR)/maze

testsuite: $(OBJDIR)/testsuite.o $(OBJDIR)/CoordinateQueueTest.o \
	$(OBJDIR)/CoordinateStackTest.o
	$(CC) $(OBJDIR)/CoordinateQueueTest.o $(OBJDIR)/CoordinateStackTest.o $(OBJDIR)/testsuite.o -o $(BINDIR)/testsuite

$(OBJDIR)/BreadthFirstSolver.o: $(SRCDIR)/BreadthFirstSolver.cpp \
	$(SRCDIR)/BreadthFirstSolver.h $(SRCDIR)/MazeSolverBase.h \
	$(SRCDIR)/CoordinateQueue.h $(SRCDIR)/RecursiveBacktracker.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/BreadthFirstSolver.cpp -o $(OBJDIR)/BreadthFirstSolver.o

$(OBJDIR)/CoordinateQueue.o: $(SRCDIR)/CoordinateQueue.cpp \
	$(SRCDIR)/CoordinateQueue.h $(SRCDIR)/MazeSolverBase.h \
	$(SRCDIR)/structs.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CoordinateQueue.cpp -o $(OBJDIR)/CoordinateQueue.o

$(OBJDIR)/CoordinateQueueTest.o: $(SRCDIR)/CoordinateQueue.cpp \
	$(SRCDIR)/CoordinateQueue.h $(SRCDIR)/structs.h
	$(CC) $(CFLAGS) -c -DTESTSUITE $(SRCDIR)/CoordinateQueue.cpp -o $(OBJDIR)/CoordinateQueueTest.o

$(OBJDIR)/CoordinateStack.o: $(SRCDIR)/CoordinateStack.cpp \
	$(SRCDIR)/CoordinateStack.h $(SRCDIR)/MazeSolverBase.h \
	$(SRCDIR)/structs.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CoordinateStack.cpp -o $(OBJDIR)/CoordinateStack.o
	
$(OBJDIR)/CoordinateStackTest.o: $(SRCDIR)/CoordinateStack.cpp \
	$(SRCDIR)/CoordinateStack.h $(SRCDIR)/structs.h
	$(CC) $(CFLAGS) -c -DTESTSUITE $(SRCDIR)/CoordinateStack.cpp -o $(OBJDIR)/CoordinateStackTest.o
	
$(OBJDIR)/DepthFirstSolver.o: $(SRCDIR)/DepthFirstSolver.cpp \
	$(SRCDIR)/DepthFirstSolver.h $(SRCDIR)/MazeSolverBase.h \
	$(SRCDIR)/CoordinateStack.h $(SRCDIR)/RecursiveBacktracker.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DepthFirstSolver.cpp -o $(OBJDIR)/DepthFirstSolver.o

$(OBJDIR)/MazeGrid.o: $(SRCDIR)/MazeGrid.cpp $(SRCDIR)/MazeGrid.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/MazeGrid.cpp -o $(OBJDIR)/MazeGrid.o
	
$(OBJDIR)/MazeSolverApp.o: $(SRCDIR)/MazeSolverApp.cpp \
	$(SRCDIR)/MazeSolverApp.h $(SRCDIR)/RecursiveBacktracker.h \
	$(SRCDIR)/MazeGrid.h $(SRCDIR)/MazeSolverBase.h \
	$(SRCDIR)/DepthFirstSolver.h $(SRCDIR)/BreadthFirstSolver.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/MazeSolverApp.cpp -o $(OBJDIR)/MazeSolverApp.o

$(OBJDIR)/RecursiveBacktracker.o: $(SRCDIR)/RecursiveBacktracker.cpp \
	$(SRCDIR)/RecursiveBacktracker.h $(SRCDIR)/MazeGrid.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/RecursiveBacktracker.cpp -o $(OBJDIR)/RecursiveBacktracker.o
	
$(OBJDIR)/testsuite.o: $(SRCDIR)/testsuite.cpp $(SRCDIR)/CoordinateQueue.h \
	$(SRCDIR)/CoordinateStack.h
	$(CC) $(CFLAGS) -c -DTESTSUITE $(SRCDIR)/testsuite.cpp -o $(OBJDIR)/testsuite.o

docs:
	doxygen

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*
	rm -rf $(DOCSDIR)/*
