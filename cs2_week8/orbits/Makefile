CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -ggdb
LDFLAGS = -lm
GLFLAGS = -L/usr/X11R6/lib -lglut -lGL -lGLU -lXi -lXmu
DOCSGEN = doxygen

SRC = src
OBJ = obj
BIN = bin
DOCS = docs

.PHONY: orbits testsuite docs clean

orbits: $(OBJ)/EulerIntegrator.o $(OBJ)/Solver.o $(SRC)/main.hpp
	$(CXX) $(SRC)/main.cpp $(OBJ)/EulerIntegrator.o \
		$(OBJ)/Solver.o $(LDFLAGS) $(GLFLAGS) -o $(BIN)/orbits

testsuite: $(OBJ)/Solver.o $(OBJ)/EulerIntegrator.o $(SRC)/testsuite.cpp
	$(CXX) $(OBJ)/Solver.o $(OBJ)/EulerIntegrator.o $(SRC)/testsuite.cpp \
		$(LDFLAGS) -o $(BIN)/testsuite

$(OBJ)/Solver.o: $(SRC)/Solver.cpp $(SRC)/Solver.hpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/Solver.cpp -o $(OBJ)/Solver.o

$(OBJ)/EulerIntegrator.o: $(SRC)/EulerIntegrator.cpp $(SRC)/EulerIntegrator.hpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/EulerIntegrator.cpp -o $(OBJ)/EulerIntegrator.o

docs:
	doxygen

clean:
	rm -f $(OBJ)/*.o $(BIN)/orbits $(BIN)/testsuite
	rm -rf $(DOCS)/*
