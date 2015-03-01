
# The testing framework will be altered to use unittest instead of simple text output

new_types: $(BIN)/datatypeTest.exe \
           $(BIN)/operatorTest \
           $(BIN)/constant_test

$(BIN)/datatypeTest.exe: $(OBJ)/datatypeTest.o 

	g++ $(OBJ)/datatypeTest.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -o $(BIN)/datatypeTest.exe

	    
$(OBJ)/swizzTest.o: $(GMATH)/swizzTest.cpp \
                    $(GMATH)/swizzTest.hpp \
                    $(GMATH)/datatype.hpp \
                    $(GMATH)/constant.hpp

	g++ -c $(GMATH)/swizzTest.cpp $(COM) \
	    -o $(OBJ)/swizzTest.o
	

$(OBJ)/datatypeTest.o: $(GMATH)/datatypeTest.cpp \
                       $(GMATH)/datatype.hpp \
                       $(GMATH)/constant.hpp

	g++ -c $(GMATH)/datatypeTest.cpp $(COM) \
	    -o $(OBJ)/datatypeTest.o

$(BIN)/operatorTest:    $(OBJ)/operatorTest.o \
                        $(OBJ)/op.o
                     
	g++ $(OBJ)/operatorTest.o \
	    $(OBJ)/op.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -o $(BIN)/operatorTest
	    
$(OBJ)/operatorTest.o:    $(GMATH)/operatorTest.cpp \
                          $(GMATH)/op.hpp \
                          $(GMATH)/datatype.hpp \
                          $(GMATH)/constant.hpp
	g++ -c $(GMATH)/operatorTest.cpp $(COM) \
            -o $(OBJ)/operatorTest.o

$(OBJ)/op.o:    $(GMATH)/op.cpp \
                $(GMATH)/op.hpp \
                $(GMATH)/datatype.hpp \
                $(GMATH)/constant.hpp
	g++ -c $(GMATH)/op.cpp $(COM) \
            -o $(OBJ)/op.o
            
$(BIN)/constant_test: $(OBJ)/constant_test.o

	g++ $(OBJ)/constant_test.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -o $(BIN)/constant_test
	    
$(OBJ)/constant_test.o: $(GMATH)/constant_test.cpp \
                        $(GMATH)/constant.hpp
	g++ -c $(GMATH)/constant_test.cpp $(COM) \
	    -L ../../dev_lib -lUnitTest++ \
	    -o $(OBJ)/constant_test.o
#$(OBJ)/type.o: $(GMATH)/type.cpp $(GMATH)/type.hpp $(GMATH)/datatypes.hpp
#	g++ -c $(GMATH)/type.cpp $(COM) -o $(OBJ)/type.o
#$(OBJ)/datatypes.o: $(GMATH)/datatypes.cpp $(GMATH)/datatypes.hpp $(GMATH)/type_op.hpp
#	g++ -c $(GMATH)/datatypes.cpp $(COM) -o $(OBJ)/datatypes.o
	