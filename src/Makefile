
# Groupe 2 : 3V-CUBE

# Makefile


FLAGS= -std=c++14 -pthread -lncurses -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
CXX= g++
MAIN= main.cpp
OUT= tetris


all: $(OUT)

$(OUT): Grid.o Tetriminos.o Block.o Game.o GUI.o  $(MAIN)
	$(CXX) $(FLAGS) $(MAIN) Block.o Grid.o Game.o GUI.o Tetriminos.o   -o $(OUT)

Grid.o: Grid.cpp Grid.hpp
	$(CXX) $(FLAGS) -c Grid.cpp


Tetriminos.o: Tetriminos.cpp Tetriminos.hpp
	$(CXX) $(FLAGS) -c Tetriminos.cpp


Block.o: Block.cpp Block.hpp
	$(CXX) $(FLAGS) -c Block.cpp


Game.o: Game.cpp Game.hpp
	$(CXX) $(FLAGS) -c Game.cpp


GUI.o: GUI.cpp GUI.hpp
	$(CXX) $(FLAGS) -c GUI.cpp



.PHONY : clean
clean:
	rm *.o *.out;