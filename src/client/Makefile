# Groupe 2 : 3V-CUBE

# Makefile

CXX= g++
MAIN= main.cpp
OUT= main
CXXFLAGS= -std=c++17 -w -lform -pthread -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override  -lsfml-graphics -lsfml-window -lsfml-system -lpthread
CXXPOSTFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread
all: $(OUT)

$(OUT):		 					Board_CLI.o Board_GUI.o CSVparser.o SettingMenu.o SettingKeys.o Connection.o Player.o PacketManager.o GameManager.o WizardLogger.o CLI.o  Client.o Mode.o  Grid.o Marathon.o Sprint.o Classic.o Tetriminos.o Block.o Vs.o SalonChat.o FriendsManager.o StatisticsManager.o $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) 	Board_CLI.o Board_GUI.o CSVparser.o SettingsMenu.o SettingKeys.o Connection.o Player.o PacketManager.o GameManager.o WizardLogger.o CLI.o Client.o Mode.o Grid.o Marathon.o Sprint.o Classic.o Tetriminos.o Block.o Vs.o SalonChat.o FriendsManager.o StatisticsManager.o -lncurses -lform -o $(OUT) $(CXXPOSTFLAGS)
CSVparser.o: ../dependencies/CSVparser/CSVparser.cpp ../dependencies/CSVparser/CSVparser.hpp
	$(CXX) $(CXXFLAGS) -c ../dependencies/CSVparser/CSVparser.cpp	
	
SettingMenu.o: SettingsMenu.cpp SettingsMenu.hpp
	$(CXX) $(CXXFLAGS) -c SettingsMenu.cpp

SettingsKeys.o: SettingKeys.cpp SettingKeys.hpp
	$(CXX) $(CXXFLAGS) -c SettingKeys.cpp
	
PacketManager.o: PacketManager.cpp PacketManager.hpp
	$(CXX) $(CXXFLAGS) -c PacketManager.cpp
	
GameManager.o: GameManager.cpp GameManager.hpp
	$(CXX) $(CXXFLAGS) -c GameManager.cpp
	
Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp
	
Connection.o: Connection.cpp Connection.hpp
	$(CXX) $(CXXFLAGS) -c Connection.cpp
	
SalonChat.o: SalonChat.cpp SalonChat.hpp
	$(CXX) $(CXXFLAGS) -c SalonChat.cpp

FriendsManager.o: FriendsManager.cpp FriendsManager.hpp
	$(CXX) $(CXXFLAGS) -c FriendsManager.cpp

StatisticsManager.o: StatisticsManager.cpp StatisticsManager.hpp
	$(CXX) $(CXXFLAGS) -c StatisticsManager.cpp

CLI.o: CLI.cpp CLI.hpp
	$(CXX) $(CXXFLAGS) -c CLI.cpp

Board_GUI.o: GUI/Board_GUI.hpp GUI/Board_GUI.cpp
	$(CXX) $(CXXFLAGS) -c GUI/Board_GUI.cpp

WizardLogger.o: ../common/WizardLogger.cpp ../common/WizardLogger.hpp
	$(CXX) $(CXXFLAGS) -c ../common/WizardLogger.cpp

Client.o: Client.cpp Client.hpp
	$(CXX) $(CXXFLAGS) -c Client.cpp

Mode.o: ../game/Mode/Mode.cpp ../game/Mode/Mode.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Mode.cpp

Vs.o: ../game/Mode/Vs.cpp ../game/Mode/Vs.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Vs.cpp

Marathon.o: ../game/Mode/Marathon.cpp ../game/Mode/Marathon.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Marathon.cpp

Sprint.o: ../game/Mode/Sprint.cpp ../game/Mode/Sprint.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Sprint.cpp

Classic.o: ../game/Mode/Classic.cpp ../game/Mode/Classic.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Mode/Classic.cpp

Board_CLI.o: CLI/Board_CLI.cpp CLI/Board_CLI.hpp
	$(CXX) $(CXXFLAGS) -c CLI/Board_CLI.cpp

Grid.o:  ../game/Game_system/Grid.cpp  ../game/Game_system/Grid.hpp
	$(CXX) $(CXXFLAGS) -c  ../game/Game_system/Grid.cpp

Tetriminos.o:  ../game/Game_system/Tetriminos.cpp  ../game/Game_system/Tetriminos.hpp
	$(CXX) $(CXXFLAGS) -c  ../game/Game_system/Tetriminos.cpp

Block.o: ../game/Game_system/Block.cpp  ../game/Game_system/Block.hpp
	$(CXX) $(CXXFLAGS) -c ../game/Game_system/Block.cpp
