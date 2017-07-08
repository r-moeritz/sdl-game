#OBJS specifies which files to compile as part of the project
OBJS := $(wildcard *.cc)

#CC specifies which compiler we're using
CXX := g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS := -IE:\mingw_dev\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS := -LE:\mingw_dev\lib -DDEBUG

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
CXXFLAGS := -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME := game

#This is the target that compiles our executable
all : $(OBJS)
	$(CXX) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CXXFLAGS) $(LDFLAGS) -o $(OBJ_NAME)
