CC = g++
LD = g++
CFLAGS = -Wall -ansi -pedantic -ggdb `sdl-config --cflags` -std=c++0x
SDLLIBS = `sdl-config --libs`
SRCDIR = src
OBJDIR = obj
BINDIR = bin

seamcarve: $(OBJDIR)/SeamCarveApp.o
	$(LD) $(OBJDIR)/SeamCarveApp.o $(SDLLIBS) -o $(BINDIR)/seamcarve

$(OBJDIR)/SeamCarveApp.o: $(SRCDIR)/SeamCarveApp.cpp $(SRCDIR)/SeamCarveApp.h
	$(CC) -c $(SRCDIR)/SeamCarveApp.cpp $(CFLAGS) -o $(OBJDIR)/SeamCarveApp.o
	
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*
