
# Groupe 2 : 3V-CUBE

# Makefile

CXX= g++
MAIN= main.cpp
OUT= main
CXXFLAGS= -std=c++17 -w -pthread -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -ldl -lm
all: $(OUT)

$(OUT): 					   Connection.o Player.o sqlite3.o Database.o PacketManager.o WizardLogger.o PlayerManager.o Room.o Global.o Server.o Mode.o Grid.o Tetriminos.o Block.o Vs.o Sprint.o PowerUp.o Classic.o Marathon.o $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) Connection.o Player.o sqlite3.o Database.o PacketManager.o WizardLogger.o PlayerManager.o Room.o Global.o Server.o Mode.o Grid.o Tetriminos.o Block.o Vs.o Sprint.o PowerUp.o Classic.o Marathon.o -o $(OUT) -lncurses -ldl -lm
	
sqlite3.o: ./database/sqlite3.c ./database/sqlite3.h
	gcc -c ./database/sqlite3.c
	
Database.o: Database.cpp Database.hpp
	$(CXX) $(CXXFLAGS) -c Database.cpp
	
PacketManager.o: PacketManager.cpp PacketManager.hpp
	$(CXX) $(CXXFLAGS) -c PacketManager.cpp
	
PlayerManager.o: PlayerManager.cpp PlayerManager.hpp
	$(CXX) $(CXXFLAGS) -c PlayerManager.cpp
	
Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp
	
Connection.o: Connection.cpp Connection.hpp
	$(CXX) $(CXXFLAGS) -c Connection.cpp

Global.o: Global.cpp Global.hpp
	$(CXX) $(CXXFLAGS) -c Global.cpp

Server.o: Server.cpp Server.hpp
	$(CXX) $(CXXFLAGS) -c Server.cpp

Room.o: Room.cpp Room.hpp
	$(CXX) $(CXXFLAGS) -c Room.cpp
	
WizardLogger.o: ../common/WizardLogger.cpp ../common/WizardLogger.hpp
	$(CXX) $(CXXFLAGS) -c ../common/WizardLogger.cpp

Mode.o: ../game/Mode/Mode.cpp ../game/Mode/Mode.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Mode.cpp

Vs.o: ../game/Mode/Vs.cpp ../game/Mode/Vs.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Vs.cpp

Marathon.o: ../game/Mode/Marathon.cpp ../game/Mode/Marathon.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Marathon.cpp

Sprint.o: ../game/Mode/Sprint.cpp ../game/Mode/Sprint.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Sprint.cpp

PowerUp.o: ../game/Mode/PowerUp.cpp ../game/Mode/PowerUp.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/PowerUp.cpp

Classic.o: ../game/Mode/Classic.cpp ../game/Mode/Classic.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Classic.cpp

Grid.o:  ../game/Game_system/Grid.cpp  ../game/Game_system/Grid.hpp
	$(CXX) $(CXXFLAGS) -c  ../game/Game_system/Grid.cpp

Tetriminos.o:  ../game/Game_system/Tetriminos.cpp  ../game/Game_system/Tetriminos.hpp
	$(CXX) $(CXXFLAGS) -c  ../game/Game_system/Tetriminos.cpp

Block.o: ../game/Game_system/Block.cpp  ../game/Game_system/Block.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Game_system/Block.cpp
