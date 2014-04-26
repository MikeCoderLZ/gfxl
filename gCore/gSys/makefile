
systemTests: $(BIN)/referenceManagerTest.exe

	
$(BIN)/referenceManagerTest.exe: $(OBJ)/referenceManagerTest.o $(OBJ)/referenceManager.o
	g++ $(OBJ)/referenceManagerTest.o $(OBJ)/referenceManager.o -o $(BIN)/referenceManagerTest.exe

$(OBJ)/referenceManagerTest.o: $(GSYS)/referenceManagerTest.cpp $(GSYS)/referenceManager.hpp
	g++ -c $(GSYS)/referenceManagerTest.cpp -o $(OBJ)/referenceManagerTest.o

$(OBJ)/referenceManager.o: $(GSYS)/referenceManager.cpp $(GSYS)/referenceManager.hpp
	g++ -c $(COM) $(GSYS)/referenceManager.cpp -o $(OBJ)/referenceManager.o