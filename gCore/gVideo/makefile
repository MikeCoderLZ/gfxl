

video_tests: $(BIN)/videoManagerTest.exe \
             $(BIN)/shadingTest.exe \
             $(BIN)/video_system_test

$(BIN)/video_system_test: $(OBJ)/video_system_test.o \
                           $(OBJ)/video_debug.o \
                           $(OBJ)/gl_core_3_3.o
                           
	g++ $(OBJ)/video_system_test.o \
	    $(OBJ)/video_debug.o \
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

$(OBJ)/video_debug.o: $(GVID)/video.cpp \
                      $(GVID)/video.hpp \
                      $(GVID)/version.hpp \
                      $(GVID)/video_system.cpp \
                      $(GVID)/video_system.hpp \
                      $(GVID)/window.cpp \
                      $(GVID)/window.hpp \
                      $(GVID)/context.cpp \
                      $(GVID)/context.hpp \
                      $(GVID)/buffer.cpp \
                      $(GVID)/buffer.hpp \
                      $(GVID)/shader.cpp \
                      $(GVID)/shader.hpp \
                      $(GVID)/gfx_exception.hpp \
                      $(GVID)/gl_core_3_3.hpp \
                      $(GMATH)/datatype.hpp
	g++ -c $(COM) -Wno-sign-compare -D DEBUG \
	    $(GVID)/video.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video_debug.o

$(OBJ)/video.o: $(GVID)/video.cpp \
                $(GVID)/video.hpp \
                $(GVID)/version.hpp \
                $(GVID)/video_system.cpp \
                $(GVID)/video_system.hpp \
                $(GVID)/window.cpp \
                $(GVID)/window.hpp \
                $(GVID)/context.cpp \
                $(GVID)/context.hpp \
                $(GVID)/buffer.cpp \
                $(GVID)/buffer.hpp \
                $(GVID)/shader.cpp \
                $(GVID)/shader.hpp \
                $(GVID)/gfx_exception.hpp \
                $(GVID)/gl_core_3_3.hpp \
                $(GMATH)/datatype.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GVID)/video.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video.o
		
$(BIN)/shadingTest.exe: $(OBJ)/shadingTest.o \
                        $(OBJ)/videoManager.o \
                        $(OBJ)/utility.o \
                        $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/shadingTest.o \
	    $(OBJ)/videoManager.o \
	    $(OBJ)/utility.o \
	    $(OBJ)/gl_core_3_3.o \
	    $(SDLLIBS) -o $(BIN)/shadingTest.exe

$(OBJ)/shadingTest.o: $(GVID)/shadingTest.cpp \
                      $(GVID)/videoManager.hpp \
                      $(GVID)/gl_core_3_3.hpp \
                      $(GVID)/checkError.hpp
	g++ -c $(COM) -Wno-sign-compare $(GVID)/shadingTest.cpp \
	    $(SDLFLAGS) -o $(OBJ)/shadingTest.o

$(BIN)/videoManagerTest.exe: $(OBJ)/videoManagerTest.o \
                             $(OBJ)/videoManager.o \
                             $(OBJ)/utility.o \
                             $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/videoManagerTest.o \
	    $(OBJ)/videoManager.o \
	    $(OBJ)/utility.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    $(SDLLIBS) \
	    -o $(BIN)/videoManagerTest.exe

$(OBJ)/videoManagerTest.o: $(GVID)/videoManagerTest.cpp \
                           $(GVID)/videoManager.hpp \
                           $(GVID)/gl_core_3_3.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GVID)/videoManagerTest.cpp \
	    $(SDLFLAGS) -o $(OBJ)/videoManagerTest.o

$(OBJ)/videoManager.o: $(GVID)/videoManager.cpp \
                       $(GVID)/videoManager.hpp \
                       $(GVID)/gl_core_3_3.hpp \
                       $(GMATH)/datatype.hpp \
                       $(GVID)/checkError.hpp
	g++ -c $(COM) -Wno-sign-compare $(GVID)/videoManager.cpp \
	    $(SDLFLAGS) -o $(OBJ)/videoManager.o
	
$(OBJ)/gl_core_3_3.o: $(GVID)/gl_core_3_3.cpp \
                      $(GVID)/gl_core_3_3.hpp
	g++ -c $(COM) $(GVID)/gl_core_3_3.cpp \
	    -o $(OBJ)/gl_core_3_3.o