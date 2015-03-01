game_tests: bomino

program_tests: $(BIN)/program_shader_test $(BIN)/program_laboratory

$(BIN)/bomino: $(OBJ)/bomino.o \
                            $(OBJ)/video.o \
                            $(OBJ)/buffer.o \
                            $(OBJ)/program.o \
                            $(OBJ)/texture.o \
                            $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/bomino.o \
	    $(OBJ)/video.o \
	    $(OBJ)/buffer.o \
	    $(OBJ)/program.o \
	    $(OBJ)/texture.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -lfreeimage \
	    $(SDLLIBS) -o $(BIN)/bomino
    
$(OBJ)/bomino.o: $(GSCN)/bomino.cpp \
                              $(GVID)/video.hpp \
                              $(GSCN)/buffer.hpp \
                              $(GSCN)/program.hpp \
                              $(GVID)/gl_core_3_3.hpp \
                              $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GSCN)/bomino.cpp \
	    $(SDLFLAGS) -o $(OBJ)/bomino.o