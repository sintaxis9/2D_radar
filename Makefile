CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system
EXEC = radar_2d
SRC = src/main.cpp src/Radar.cpp src/Object.cpp
OBJ = $(SRC:.cpp=.o)

SFML_INCLUDE = $(shell nix-shell -p sfml --run "echo $SFML_INCLUDE_DIR")
SFML_LIB = $(shell nix-shell -p sfml --run "echo $SFML_LIBRARY_DIR")

all: $(EXEC)
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I$(SFML_INCLUDE) $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
fclean: clean
	rm -f $(EXEC)
re: fclean all
