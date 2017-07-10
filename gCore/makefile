COM = -Wall -std=c++0x
OBJ = ./obj
BIN = ./bin
SRC = ./src
SDLLIBS := $(shell sdl2-config --libs)
SDLLIBS += -lX11 -lGL

SDLFLAGS := $(shell sdl2-config --cflags)
# SDLFLAGS += -IC:/MinGW/include/GL3

MATHOBJ = $(OBJ)/vec.o $(OBJ)/op.o $(OBJ)/matrix.o $(OBJ)/quaternion.o
MATHDPND = vec.o op.o matrix.o quaternion.o

GMATH := ./gMath
GSYS := ./gSys
GVID := ./gVideo
GSCN := ./gScene
GUTIL := ./gUtility
GGAME := ./gGame


include ./gMath/makefile
include ./gUtility/makefile
include ./gSys/makefile
include ./gVideo/makefile
include ./gScene/makefile
include ./gGame/makefile


all: systemTests video_tests scene_tests new_types

gEngine.exe: $(OBJ)/gEngine.o $(MATHOBJ) makefile
	g++ $(OBJ)/gEngine.o $(MATHOBJ) $(SDLLIBS) -o $(BIN)/gEngine.exe

$(OBJ)/gEngine.o: $(SRC)/gEngine.cpp $(SRC)/gMath.hpp
	g++ -c $(COM) $(SRC)/gEngine.cpp $(SDLFLAGS) -o $(OBJ)/gEngine.o

docs: FORCE
	doxygen doxyfile
	
clean: FORCE
	rm $(OBJ)/*.o
	
FORCE: