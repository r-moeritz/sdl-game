OBJS := $(wildcard src/*.cc)
CXX := g++
RM := del
INCLUDE_PATHS := -Iinclude
LIBRARY_PATHS := -DDEBUG

# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
CXXFLAGS := -w -Wl,-subsystem,windows

LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
OBJ_NAME := game.exe

.PHONY: all clean

all : $(OBJS)
	$(CXX) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CXXFLAGS) $(LDFLAGS) -o $(OBJ_NAME)

clean:
	$(RM) $(OBJ_NAME)
