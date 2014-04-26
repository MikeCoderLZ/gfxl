

videoTests: $(BIN)/videoManagerTest.exe $(BIN)/shadingTest.exe

$(BIN)/shadingTest.exe: $(OBJ)/shadingTest.o $(OBJ)/videoManager.o $(OBJ)/utility.o $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/shadingTest.o $(OBJ)/videoManager.o $(OBJ)/utility.o $(OBJ)/gl_core_3_3.o $(SDLLIBS) -o $(BIN)/shadingTest.exe

$(OBJ)/shadingTest.o: $(GVID)/shadingTest.cpp $(GVID)/videoManager.hpp $(GVID)/gl_core_3_3.hpp $(GVID)/checkError.hpp
	g++ -c $(COM) $(GVID)/shadingTest.cpp $(SDLFLAGS) -o $(OBJ)/shadingTest.o

$(BIN)/videoManagerTest.exe: $(OBJ)/videoManagerTest.o $(OBJ)/videoManager.o $(OBJ)/utility.o $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/videoManagerTest.o $(OBJ)/videoManager.o $(OBJ)/utility.o $(OBJ)/gl_core_3_3.o $(SDLLIBS) -o $(BIN)/videoManagerTest.exe

$(OBJ)/videoManagerTest.o: $(GVID)/videoManagerTest.cpp $(GVID)/videoManager.hpp $(GVID)/gl_core_3_3.hpp
	g++ -c $(COM) $(GVID)/videoManagerTest.cpp $(SDLFLAGS) -o $(OBJ)/videoManagerTest.o

$(OBJ)/videoManager.o: $(GVID)/videoManager.cpp $(GVID)/videoManager.hpp $(GVID)/gl_core_3_3.hpp $(GMATH)/datatype.hpp $(GVID)/checkError.hpp
	g++ -c $(COM) $(GVID)/videoManager.cpp $(SDLFLAGS) -o $(OBJ)/videoManager.o
	
$(OBJ)/gl_core_3_3.o: $(GVID)/gl_core_3_3.cpp $(GVID)/gl_core_3_3.hpp
	g++ -c $(COM) $(GVID)/gl_core_3_3.cpp -o $(OBJ)/gl_core_3_3.o