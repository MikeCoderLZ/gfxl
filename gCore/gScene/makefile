scene_tests: texture_tests camera_tests

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
	    
camera_tests: $(BIN)/camera_test
	    
$(BIN)/camera_test: $(OBJ)/camera_test.o \
                    $(OBJ)/camera.o \
                    $(OBJ)/op.o \
                    $(OBJ)/video.o \
                    $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/camera_test.o \
	$(OBJ)/camera.o \
	$(OBJ)/video.o \
	$(OBJ)/op.o \
	$(OBJ)/gl_core_3_3.o \
	-L ../../dev_lib -lUnitTest++ \
	$(SDLLIBS) -o $(BIN)/camera_test
	    
$(OBJ)/camera_test.o: $(GSCN)/camera_test.cpp \
                      $(GSCN)/camera.hpp \
                      $(GVID)/gfx_exception.hpp \
                      $(GVID)/video.hpp \
                      $(GVID)/version.hpp \
                      $(GVID)/window.hpp \
                      $(GVID)/context.hpp \
                      $(GVID)/buffer.hpp \
                      $(GVID)/program.hpp
	g++ -c $(COM) \
	$(GSCN)/camera_test.cpp \
	 $(SDLFLAGS) -o $(OBJ)/camera_test.o
    
$(OBJ)/camera.o: $(GSCN)/camera.cpp \
                 $(GSCN)/camera.hpp \
                 $(GMATH)/datatype.hpp \
                 $(GMATH)/op.hpp \
                 $(GVID)/gfx_exception.hpp \
                 $(GVID)/video.hpp \
                 $(GVID)/version.hpp \
                 $(GVID)/window.hpp \
                 $(GVID)/context.hpp \
                 $(GVID)/buffer.hpp \
                 $(GVID)/program.hpp
	g++ -c $(COM) \
	$(GSCN)/camera.cpp \
	$(SDLFLAGS) -o $(OBJ)/camera.o