CXX = g++
MAIN = main.cpp
OUT= main
CXXFLAGS = -std=c++17 -w
CXXPOSTFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread
all: $(OUT)

$(OUT): $(MAIN) Classic.o Vs.o Grid.o Tetriminos.o Block.o Mode.o Board.o 
	$(CXX) $(CXXFLAGS) $(MAIN) Classic.o Vs.o Grid.o Tetriminos.o Block.o Mode.o Board.o $(CXXPOSTFLAGS)

Board.o: Board.hpp Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

Classic.o: Mode/Classic.cpp Mode/Classic.hpp
	$(CXX) $(CXXFLAGS) -c Mode/Classic.cpp

Vs.o: Mode/Vs.cpp Mode/Vs.hpp
	$(CXX) $(CXXFLAGS) -c Mode/Vs.cpp

Grid.o:  Game_system/Grid.cpp  Game_system/Grid.hpp
	$(CXX) $(CXXFLAGS) -c  Game_system/Grid.cpp

Tetriminos.o:  Game_system/Tetriminos.cpp  Game_system/Tetriminos.hpp
	$(CXX) $(CXXFLAGS) -c  Game_system/Tetriminos.cpp

Block.o: Game_system/Block.cpp  Game_system/Block.hpp
	$(CXX) $(CXXFLAGS) -c Game_system/Block.cpp

Mode.o: Mode/Mode.cpp Mode/Mode.hpp
	$(CXX) $(CXXFLAGS) -c Mode/Mode.cpp