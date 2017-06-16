scene_tests: texture_tests camera_tests program_tests light_tests scene_test

scene_test: $(BIN)/scene_test

$(BIN)/scene_test: $(OBJ)/scene_test.o \
                   $(OBJ)/gl_core_3_3.o \
                   $(OBJ)/buffer.o \
                   $(OBJ)/vertex_buffer.o \
                   $(OBJ)/program.o \
                   $(OBJ)/light.o \
                   $(OBJ)/camera.o \
                   $(OBJ)/video.o \
                   $(OBJ)/op.o

	g++ $(OBJ)/scene_test.o \
	    $(OBJ)/gl_core_3_3.o \
	    $(OBJ)/buffer.o \
	    $(OBJ)/vertex_buffer.o \
	    $(OBJ)/program.o \
	    $(OBJ)/light.o \
	    $(OBJ)/camera.o \
	    $(OBJ)/video.o \
	    $(OBJ)/op.o \
	    -L ../../dev_lib -lUnitTest++ \
	    $(SDLLIBS) -o $(BIN)/scene_test

$(OBJ)/scene_test.o: $(GSCN)/scene_test.cpp \
                     $(GVID)/video.hpp \
                     $(GMATH)/datatype.hpp \
                     $(GMATH)/constant.hpp \
                     $(GSCN)/buffer.hpp \
                     $(GSCN)/program.hpp \
                     $(GSCN)/light.hpp \
                     $(GSCN)/camera.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/scene_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/scene_test.o

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
                       $(GVID)/context.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/texture_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/texture_test.o

$(OBJ)/texture.o: $(GSCN)/texture.cpp \
                  $(GSCN)/texture.hpp \
                  $(GVID)/gfx_exception.hpp \
                  $(GVID)/video.hpp \
                  $(GVID)/version.hpp \
                  $(GVID)/window.hpp \
                  $(GVID)/context.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/texture.cpp \
	    $(SDLFLAGS) -o $(OBJ)/texture.o
	    
$(OBJ)/buffer.o: $(GSCN)/buffer.cpp \
                 $(GSCN)/buffer.hpp \
                 $(GVID)/video.hpp \
                 $(GVID)/gfx_exception.hpp \
                 $(GVID)/version.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/buffer.cpp \
	    $(SDLFLAGS) -o $(OBJ)/buffer.o
	    
$(OBJ)/vertex_buffer.o: $(GSCN)/vertex_buffer.cpp \
                        $(GSCN)/vertex_buffer.hpp \
                        $(GSCN)/buffer.hpp \
                        $(GVID)/video.hpp \
                        $(GVID)/gfx_exception.hpp \
                        $(GVID)/version.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/vertex_buffer.cpp \
	    $(SDLFLAGS) -o $(OBJ)/vertex_buffer.o
	    
$(OBJ)/program.o: $(GSCN)/program.cpp \
                  $(GSCN)/program.hpp \
                  $(GVID)/video.hpp \
                  $(GVID)/gfx_exception.hpp \
                  $(GVID)/version.hpp
	g++ -c $(COM) -Wno-sign-compare \
	    $(GSCN)/program.cpp \
	    $(SDLFLAGS) -o $(OBJ)/program.o
	    
program_tests: $(BIN)/program_shader_test $(BIN)/program_laboratory
	    
$(BIN)/program_laboratory: $(OBJ)/program_laboratory.o \
                            $(OBJ)/video.o \
                            $(OBJ)/buffer.o \
                            $(OBJ)/vertex_buffer.o \
                            $(OBJ)/program.o \
                            $(OBJ)/texture.o \
                            $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/program_laboratory.o \
	    $(OBJ)/video.o \
	    $(OBJ)/buffer.o \
	    $(OBJ)/vertex_buffer.o \
	    $(OBJ)/program.o \
	    $(OBJ)/texture.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -lfreeimage \
	    $(SDLLIBS) -o $(BIN)/program_laboratory

$(OBJ)/program_laboratory.o: $(GSCN)/program_laboratory.cpp \
                              $(GVID)/video.hpp \
                              $(GSCN)/buffer.hpp \
                              $(GSCN)/vertex_buffer.hpp \
                              $(GSCN)/program.hpp \
                              $(GVID)/gl_core_3_3.hpp \
                              $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GSCN)/program_laboratory.cpp \
	    $(SDLFLAGS) -o $(OBJ)/program_laboratory.o
	    
$(BIN)/program_shader_test: $(OBJ)/program_shader_test.o \
                            $(OBJ)/video.o \
                            $(OBJ)/vertex_buffer.o \
                            $(OBJ)/buffer.o \
                            $(OBJ)/program.o \
                            $(OBJ)/texture.o \
                            $(OBJ)/camera.o \
                            $(OBJ)/op.o \
                            $(OBJ)/gl_core_3_3.o
	g++ $(OBJ)/program_shader_test.o \
	    $(OBJ)/video.o \
	    $(OBJ)/vertex_buffer.o \
	    $(OBJ)/buffer.o \
	    $(OBJ)/program.o \
	    $(OBJ)/texture.o \
	    $(OBJ)/camera.o \
	    $(OBJ)/op.o \
	    $(OBJ)/gl_core_3_3.o \
	    -L ../../dev_lib -lUnitTest++ \
	    -lfreeimage \
	    $(SDLLIBS) -o $(BIN)/program_shader_test

$(OBJ)/program_shader_test.o: $(GSCN)/program_shader_test.cpp \
                              $(GVID)/video.hpp \
                              $(GSCN)/vertex_buffer.hpp \
                              $(GSCN)/buffer.hpp \
                              $(GSCN)/program.hpp \
                              $(GSCN)/texture.hpp \
                              $(GSCN)/camera.hpp \
                              $(GVID)/gl_core_3_3.hpp \
                              $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	    -Wno-sign-compare -Wno-unused-but-set-variable \
	    $(GSCN)/program_shader_test.cpp \
	    $(SDLFLAGS) -o $(OBJ)/program_shader_test.o          
	    
	    
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
                      $(GSCN)/buffer.hpp \
                      $(GSCN)/program.hpp
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
                 $(GSCN)/buffer.hpp \
                 $(GSCN)/program.hpp
	g++ -c $(COM) \
	$(GSCN)/camera.cpp \
	$(SDLFLAGS) -o $(OBJ)/camera.o
	
light_tests: $(BIN)/light_test

$(BIN)/light_test: $(OBJ)/light_test.o \
                   $(OBJ)/light.o \
                   $(OBJ)/light.o \
                   $(OBJ)/gl_core_3_3.o
#                    $(OBJ)/op.o \
#                    $(OBJ)/video.o \

	g++ $(OBJ)/light_test.o \
	$(OBJ)/light.o \
	$(OBJ)/op.o \
	$(OBJ)/gl_core_3_3.o \
	-L ../../dev_lib -lUnitTest++ \
	$(SDLLIBS) -o $(BIN)/light_test
	    
$(OBJ)/light_test.o: $(GSCN)/light_test.cpp \
                      $(GSCN)/light.hpp \
#                       $(GVID)/gfx_exception.hpp \
#                       $(GVID)/video.hpp \
#                       $(GVID)/version.hpp \
#                       $(GVID)/window.hpp \
#                       $(GVID)/context.hpp \
#                       $(GSCN)/buffer.hpp \
#                       $(GSCN)/program.hpp
	g++ -c $(COM) \
	$(GSCN)/light_test.cpp \
	 $(SDLFLAGS) -o $(OBJ)/light_test.o

$(OBJ)/light.o: $(GSCN)/light.cpp \
                $(GSCN)/light.hpp \
                $(GSCN)/program.hpp \
                $(GMATH)/datatype.hpp \
                $(GMATH)/op.hpp \
                $(GSCN)/uniform.hpp \
                $(GVID)/gl_core_3_3.hpp \
#                  $(GVID)/gfx_exception.hpp \
#                  $(GVID)/video.hpp \
#                  $(GVID)/version.hpp \
#                  $(GVID)/window.hpp \
#                  $(GVID)/context.hpp \
#                  $(GSCN)/buffer.hpp \
#                  $(GSCN)/program.hpp
	g++ -c $(COM) \
	$(GSCN)/light.cpp \
	$(SDLFLAGS) -o $(OBJ)/light.o
	
geometry_tests: $(OBJ)/primitive.o

$(OBJ)/primitive.o: $(GSCN)/primitive.cpp \
                    $(GSCN)/primitive.hpp \
                    $(GSCN)/buffer.hpp \
                    $(GSCN)/orientable.hpp \
                    $(GMATH)/datatype.hpp
	g++ -c $(COM) \
	$(GSCN)/primitive.cpp \
	$(SDLFLAGS) -o $(OBJ)/primitive.o