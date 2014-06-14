texture_tests: $(BIN)/texture_test

$(BIN)/texture_test: $(OBJ)/texture_test.o \
                     $(OBJ)/texture.o \
                     $(OBJ)/video.o \
                     $(OBJ)/gl_core_3_3.o
                     
	g++ $(OBJ)/texture_test.o \
	    $(OBJ)/texture.o \
	    $(OBJ)/video.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -lfreeimage \
	    $(SDLLIBS) -o $(BIN)/texture_test

$(OBJ)/texture_test.o: $(GSCN)/texture_test.cpp \
                       $(GSCN)/texture.hpp \
                       $(GVID)/gfx_exception.hpp \
                       $(GVID)/video.hpp \
                       $(GVID)/version.hpp \
                       $(GVID)/window.hpp \
                       $(GVID)/context.hpp \
                       $(GVID)/buffer.hpp \
                       $(GVID)/program.hpp 
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/texture_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/texture_test.o

$(OBJ)/texture.o: $(GSCN)/texture.cpp \
                  $(GSCN)/texture.hpp \
                  $(GVID)/gfx_exception.hpp \
                  $(GVID)/video.hpp \
                  $(GVID)/version.hpp \
                  $(GVID)/window.hpp \
                  $(GVID)/context.hpp \
                  $(GVID)/buffer.hpp \
                  $(GVID)/program.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/texture.cpp \
	    $(SDLFLAGS) -o $(OBJ)/texture.o