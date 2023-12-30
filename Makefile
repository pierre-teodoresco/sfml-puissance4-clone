CXX=clang++
CXXFLAGS=-std=c++17 -stdlib=libc++

PROGRAM=Puissance4

TARGET_DIR=bin/
SRC_DIR=src/

SRC_FILES=Main.cpp Application.cpp Grid.cpp Game.cpp
OBJ_FILES=$(SRC_FILES:.cpp=.o)

INCLUDE_DIR=Dependencies/SFML/include/ -I$(SRC_DIR)headers/
LIB_DIR=Dependencies/SFML/lib/
LIB_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: build

run: build
	./$(TARGET_DIR)$(PROGRAM)

build: binaries $(TARGET_DIR)$(PROGRAM) clean

binaries:
	mkdir -p $(TARGET_DIR)

$(TARGET_DIR)$(PROGRAM): $(OBJ_FILES)
	echo "Linking..."
	$(CXX) -L$(LIB_DIR) $(LIB_FLAGS) -Wl,-rpath,./$(LIB_DIR) -o $@ $^

%.o: $(SRC_DIR)%.cpp
	echo "Compiling..."
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $<

clean:
	echo "Cleaning..."
	rm -f *.o