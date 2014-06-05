

videoTests: $(BIN)/videoManagerTest.exe \
            $(BIN)/shadingTest.exe \
            $(BIN)/video_manager_test \
            $(BIN)/program_shader_test

$(BIN)/video_manager_test: $(OBJ)/video_manager_test.o \
                           $(OBJ)/video_manager.o \
                           $(OBJ)/gl_core_3_3.o
                           
	g++ $(OBJ)/video_manager_test.o \
	    $(OBJ)/video_manager.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    $(SDLLIBS) -o $(BIN)/video_manager_test

$(OBJ)/video_manager_test.o: $(GVID)/video_manager_test.cpp \
                             $(GVID)/video_manager.hpp \
                             $(GVID)/gl_core_3_3.hpp \
                             $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GVID)/video_manager_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video_manager_test.o

$(OBJ)/video_manager.o: $(GVID)/video_manager.cpp \
                        $(GVID)/video_manager.hpp \
                        $(GVID)/gl_core_3_3.hpp \
                        $(GMATH)/datatype.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GVID)/video_manager.cpp \
	    $(SDLFLAGS) -o $(OBJ)/video_manager.o

$(BIN)/program_shader_test: $(OBJ)/program_shader_test.o \
                            $(OBJ)/video_manager.o \
                            $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/program_shader_test.o \
	    $(OBJ)/video_manager.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    $(SDLLIBS) -o $(BIN)/program_shader_test
    
$(OBJ)/program_shader_test.o: $(GVID)/program_shader_test.cpp \
                              $(GVID)/video_manager.hpp \
                              $(GVID)/gl_core_3_3.hpp \
                              $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GVID)/program_shader_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/program_shader_test.o                           

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