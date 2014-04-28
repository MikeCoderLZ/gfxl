
# The testing framework will be altered to use unittest instead of simple text output
mathTests: $(BIN)/matrixTest.exe $(BIN)/vectorTest.exe $(BIN)/quaternionTest.exe


$(BIN)/matrixTest.exe: $(OBJ)/matrixTest.o \
                       $(OBJ)/matrix.o  $(OBJ)/vec.o \
                       $(OBJ)/quaternion.o  $(OBJ)/op.o
                       
	g++ $(OBJ)/matrixTest.o \
	    $(OBJ)/matrix.o  $(OBJ)/vec.o \
	    $(OBJ)/quaternion.o  $(OBJ)/op.o \
	    -o $(BIN)/matrixTest.exe

	    
$(OBJ)/matrixTest.o: $(GMATH)/matrixTest.cpp \
                     $(GMATH)/matrix.hpp  $(GMATH)/op.hpp
                     
	g++ -c $(GMATH)/matrixTest.cpp  $(COM) \
	    -o $(OBJ)/matrixTest.o

	    
$(OBJ)/matrix.o: $(GMATH)/matrix.cpp \
                 $(GMATH)/matrix.hpp  $(GMATH)/vec.hpp \
                 $(GMATH)/op.hpp  $(GMATH)/quaternion.hpp
                 
	g++ -c $(GMATH)/matrix.cpp  $(COM) \
	    -o $(OBJ)/matrix.o

	    
$(BIN)/vectorTest.exe: $(OBJ)/vectorTest.o \
                       $(OBJ)/vec.o  $(OBJ)/op.o \
                       $(OBJ)/matrix.o  $(OBJ)/quaternion.o
                       
	g++ $(OBJ)/vectorTest.o  \
	    $(OBJ)/vec.o  $(OBJ)/op.o \
	    $(OBJ)/matrix.o  $(OBJ)/quaternion.o \
	    -o $(BIN)/vectorTest.exe

	    
$(OBJ)/vectorTest.o: $(GMATH)/vectorTest.cpp \
                     $(GMATH)/vec.hpp  $(GMATH)/op.hpp
                     
	g++ -c $(GMATH)/vectorTest.cpp  $(COM) \
	    -o $(OBJ)/vectorTest.o

	    
$(OBJ)/vec.o: $(GMATH)/vec.cpp  $(GMATH)/vec.hpp

	g++ -c $(GMATH)/vec.cpp  $(COM) \
	    -o $(OBJ)/vec.o

	    
$(OBJ)/op.o: $(GMATH)/op.cpp \
             $(GMATH)/op.hpp  $(GMATH)/matrix.hpp \
             $(GMATH)/vec.hpp
             
	g++ -c $(GMATH)/op.cpp  $(COM) \
	    -o $(OBJ)/op.o

	    
$(BIN)/quaternionTest.exe: $(OBJ)/quaternionTest.o \
                           $(OBJ)/vec.o  $(OBJ)/op.o \
                           $(OBJ)/matrix.o  $(OBJ)/quaternion.o
                           
	g++ $(OBJ)/quaternionTest.o \
	    $(OBJ)/quaternion.o  $(OBJ)/vec.o \
	    $(OBJ)/op.o  $(OBJ)/matrix.o \
	    -o $(BIN)/quaternionTest.exe
	    
$(OBJ)/quaternionTest.o: $(GMATH)/quaternionTest.cpp  $(GMATH)/quaternion.hpp

	g++ -c $(GMATH)/quaternionTest.cpp  $(COM) \
	    -o $(OBJ)/quaternionTest.o


$(OBJ)/quaternion.o: $(GMATH)/quaternion.cpp \
                     $(GMATH)/quaternion.hpp  $(GMATH)/vec.hpp \
                     $(GMATH)/op.hpp  $(GMATH)/matrix.hpp

	g++ -c $(GMATH)/quaternion.cpp $(COM) -o $(OBJ)/quaternion.o

	
newTypes: $(BIN)/datatypeTest.exe


$(BIN)/datatypeTest.exe: $(OBJ)/datatypeTest.o

	g++ $(OBJ)/datatypeTest.o -o $(BIN)/datatypeTest.exe


$(OBJ)/datatypeTest.o: $(GMATH)/datatypeTest.cpp $(GMATH)/datatype.hpp

	g++ -c $(GMATH)/datatypeTest.cpp $(COM) \
	    -o $(OBJ)/datatypeTest.o
	    
	    
#$(OBJ)/type.o: $(GMATH)/type.cpp $(GMATH)/type.hpp $(GMATH)/datatypes.hpp
#	g++ -c $(GMATH)/type.cpp $(COM) -o $(OBJ)/type.o
#$(OBJ)/datatypes.o: $(GMATH)/datatypes.cpp $(GMATH)/datatypes.hpp $(GMATH)/type_op.hpp
#	g++ -c $(GMATH)/datatypes.cpp $(COM) -o $(OBJ)/datatypes.o
	