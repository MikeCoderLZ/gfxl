

video_tests: $(BIN)/shadingTest.exe \
             $(BIN)/video_system_test

$(BIN)/video_system_test: $(OBJ)/video_system_test.o \
                           $(OBJ)/video.o \
                           $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/video_system_test.o \
	    $(OBJ)/video.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    $(SDLLIBS) -o $(BIN)/video_system_test

$(OBJ)/video_system_test.o: $(GVID)/video_system_test.cpp \
                             $(GVID)/video.hpp \
                             $(GVID)/gl_core_3_3.hpp \
                             $(GMATH)/datatype.hpp
	g++ -c $(COM) -D DEBUG \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GVID)/video_system_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video_system_test.o

$(OBJ)/video.o: $(GVID)/video.cpp \
                $(GVID)/video.hpp \
                $(GVID)/version.hpp \
                $(GVID)/video_system.cpp \
                $(GVID)/video_system.hpp \
                $(GVID)/window.cpp \
                $(GVID)/window.hpp \
                $(GVID)/context.cpp \
                $(GVID)/context.hpp \
                $(GVID)/gfx_exception.hpp \
                $(GVID)/gl_core_3_3.hpp \
                $(GMATH)/datatype.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GVID)/video.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video.o
	
$(OBJ)/gl_core_3_3.o: $(GVID)/gl_core_3_3.cpp \
                      $(GVID)/gl_core_3_3.hpp
	g++ -c $(COM) $(GVID)/gl_core_3_3.cpp \
	    -o $(OBJ)/gl_core_3_3.o