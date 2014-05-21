COM = -Wall -std=c++0x
OBJ = ./obj
BIN = ./bin
SRC = ./src
SDLLIBS := $(shell sdl2-config --libs)
SDLLIBS += -lX11 -lGL

SDLFLAGS := $(shell sdl2-config --cflags)
SDLFLAGS += -IC:/MinGW/include/GL3

MATHOBJ = $(OBJ)/vec.o $(OBJ)/op.o $(OBJ)/matrix.o $(OBJ)/quaternion.o
MATHDPND = vec.o op.o matrix.o quaternion.o

GMATH := ./gMath
GSYS := ./gSys
GVID := ./gVideo
GUTIL := ./gUtility


include ./gMath/makefile
include ./gUtility/makefile
include ./gSys/makefile
include ./gVideo/makefile


all: mathTests systemTests videoTests utilities

gEngine.exe: $(OBJ)/gEngine.o $(MATHOBJ) makefile
	g++ $(OBJ)/gEngine.o $(MATHOBJ) $(SDLLIBS) -o $(BIN)/gEngine.exe

$(OBJ)/gEngine.o: $(SRC)/gEngine.cpp $(SRC)/gMath.hpp
	g++ -c $(COM) $(SRC)/gEngine.cpp $(SDLFLAGS) -o $(OBJ)/gEngine.o

clean:
	rm $(OBJ)/*.o