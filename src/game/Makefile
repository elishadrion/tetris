
# Groupe 2 : 3V-CUBE

# Makefile


FLAGS= -std=c++17 -pthread -lncurses -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
CXX= g++
MAIN= main.cpp
OUT= tetris


all: $(OUT)

$(OUT): Grid.o Tetriminos.o Block.o Mode.o GUI.o Classic.o Sprint.o Marathon.o  vsGUI.o $(MAIN)
	$(CXX) $(FLAGS) $(MAIN) Block.o Grid.o Mode.o GUI.o Tetriminos.o Classic.o Sprint.o Marathon.o  vsGUI.o -o $(OUT)

Grid.o:  ./Game_system/Grid.cpp  ./Game_system/Grid.hpp
	$(CXX) $(FLAGS) -c  ./Game_system/Grid.cpp

Tetriminos.o:  ./Game_system/Tetriminos.cpp  ./Game_system/Tetriminos.hpp
	$(CXX) $(FLAGS) -c  ./Game_system/Tetriminos.cpp


Block.o: ./Game_system/Block.cpp  ./Game_system/Block.hpp
	$(CXX) $(FLAGS) -c  ./Game_system/Block.cpp

Mode.o: ./Mode/Mode.cpp ./Mode/Mode.hpp
	$(CXX) $(FLAGS) -c ./Mode/Mode.cpp

GUI.o: ./GUI/GUI.cpp ./GUI/GUI.hpp
	$(CXX) $(FLAGS) -c ./GUI/GUI.cpp

vsGUI.o: ./GUI/vsGUI.cpp ./GUI/vsGUI.hpp
	$(CXX) $(FLAGS) -c ./GUI/vsGUI.cpp

Classic.o: ./Mode/Classic.cpp ./Mode/Classic.hpp
	$(CXX) $(FLAGS) -c ./Mode/Classic.cpp


Sprint.o: ./Mode/Sprint.cpp ./Mode/Sprint.hpp
	$(CXX) $(FLAGS) -c ./Mode/Sprint.cpp

Marathon.o: ./Mode/Marathon.cpp ./Mode/Marathon.hpp
	$(CXX) $(FLAGS) -c ./Mode/Marathon.cpp




.PHONY : clean
clean:
	rm *.o;