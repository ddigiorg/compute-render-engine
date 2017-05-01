CXX = g++
INCLUDE = -I./Source/
CFLAGS = -c -g #-Wall
LDLIBS = -lGLEW -lGL -lOpenCL -lsfml-system -lsfml-window -lsfml-graphics -lopencv_core  -lopencv_videoio -lopencv_highgui

EXECUTE = execute.exe

all: $(EXECUTE)

OBJS_E = Particles.o InputVideo.o Display.o Camera.o Shader.o Vbo.o Texture2D.o ImageMesh.o ComputeSystem.o ComputeProgram.o
$(EXECUTE): $(OBJS_E)
	$(CXX) $(LDLIBS) $(OBJS_E) -o $(EXECUTE)

# ==========
# Apps
# ==========
PATH_A = ./Source/Apps/

Particles.o: $(PATH_A)Particles/Particles.cpp
	$(CXX) $(INCLUDE) $(CFLAGS) $(PATH_A)Particles/Particles.cpp

Retina.o: $(PATH_A)Retina/Retina.cpp
	$(CXX) $(INCLUDE) $(CFLAGS) $(PATH_A)Retina/Retina.cpp

# ==========
# Input
# ==========
PATH_I = ./Source/Engine/Input/

InputVideo.o: $(PATH_I)InputVideo.cpp
	$(CXX) $(CFLAGS) $(PATH_I)InputVideo.cpp

# ==========
# Render
# ==========
PATH_R = ./Source/Engine/Render/

Display.o: $(PATH_R)Display.cpp
	$(CXX) $(CFLAGS) $(PATH_R)Display.cpp

Camera.o: $(PATH_R)Camera.cpp
	$(CXX) $(CFLAGS) $(PATH_R)Camera.cpp

Shader.o: $(PATH_R)Shader.cpp
	$(CXX) $(CFLAGS) $(PATH_R)Shader.cpp

Vbo.o: $(PATH_R)Vbo.cpp
	$(CXX) $(CFLAGS) $(PATH_R)Vbo.cpp

Texture2D.o: $(PATH_R)Texture2D.cpp
	$(CXX) $(CFLAGS) $(PATH_R)Texture2D.cpp

ImageMesh.o: $(PATH_R)ImageMesh.cpp
	$(CXX) $(CFLAGS) $(PATH_R)ImageMesh.cpp

# ==========
# Compute
# ==========
PATH_C = ./Source/Engine/Compute/

ComputeSystem.o: $(PATH_C)ComputeSystem.cpp
	$(CXX) $(CFLAGS) $(PATH_C)ComputeSystem.cpp

ComputeProgram.o: $(PATH_C)ComputeProgram.cpp
	$(CXX) $(CFLAGS) $(PATH_C)ComputeProgram.cpp

#Helpers.o: $(PATH_C)Helpers.cpp
#	$(CXX) $(CFLAGS) $(PATH_C)Helpers.cpp

# ==========
# Cleanup
# ==========
.PHONY : clean
clean:
	rm -rf *o $(EXECUTE)
