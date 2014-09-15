CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -ggdb
DOCSGEN = doxygen
LDFLAGS	= -L/usr/X11R6/lib -lglut -lGL -lGLU -lXi -lXmu -lm
SRC = src
OBJ = obj
BIN = bin
DOCS = docs

.PHONY: fourier docs

fourier: $(OBJ)/ComplexNumber.o $(OBJ)/FourierTransform.o \
$(OBJ)/SpectralSynthesizer.o $(OBJ)/Vector3D.o
	$(CXX) $(SRC)/main.cpp $(OBJ)/*.o $(CXXFLAGS) $(LDFLAGS) -o $(BIN)/fourier

docs:
	$(DOCSGEN)

$(OBJ)/ComplexNumber.o: $(SRC)/ComplexNumber.cpp $(SRC)/ComplexNumber.hpp
	$(CXX) $(SRC)/ComplexNumber.cpp -c $(CXXFLAGS) -o $(OBJ)/ComplexNumber.o

$(OBJ)/FourierTransform.o: $(SRC)/FourierTransform.cpp $(SRC)/FourierTransform.hpp \
$(SRC)/ComplexNumber.hpp
	$(CXX) $(SRC)/FourierTransform.cpp -c $(CXXFLAGS) -o $(OBJ)/FourierTransform.o

$(OBJ)/SpectralSynthesizer.o: $(SRC)/SpectralSynthesizer.cpp \
$(SRC)/SpectralSynthesizer.hpp  $(SRC)/ComplexNumber.hpp
	$(CXX) $(SRC)/SpectralSynthesizer.cpp -c $(CXXFLAGS) -o $(OBJ)/SpectralSynthesizer.o

$(OBJ)/Vector3D.o: $(SRC)/Vector3D.cpp $(SRC)/Vector3D.hpp
	$(CXX) $(SRC)/Vector3D.cpp -c $(CXXFLAGS) -o $(OBJ)/Vector3D.o

clean:
	rm -f $(OBJ)/*.o $(BIN)/fourier
	rm -rf $(DOCS)/*
