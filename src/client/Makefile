
# Groupe 2 : 3V-CUBE

# Makefile

CXX= g++
MAIN= main.cpp
OUT= main
CXXFLAGS= -std=c++17 -pthread -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
all: $(OUT)

$(OUT): Connection.o Player.o GameManager.o PacketManager.o WizardLogger.o CacheManager.o WizardDisplay.o $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) Connection.o Player.o PacketManager.o GameManager.o CacheManager.o WizardDisplay.o WizardLogger.o -o $(OUT)
	
PacketManager.o: PacketManager.cpp PacketManager.hpp
	$(CXX) $(CXXFLAGS) -c PacketManager.cpp
	
GameManager.o: GameManager.cpp GameManager.hpp
	$(CXX) $(CXXFLAGS) -c GameManager.cpp
	
CacheManager.o: CacheManager.hpp CacheManager.cpp
	$(CXX) $(CXXFLAGS) -c CacheManager.cpp
	
Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp
	
Connection.o: Connection.cpp Connection.hpp
	$(CXX) $(CXXFLAGS) -c Connection.cpp
	
WizardDisplay.o: WizardDisplay.cpp WizardDisplay.hpp
	$(CXX) $(CXXFLAGS) -c WizardDisplay.cpp
	
WizardLogger.o: ../common/WizardLogger.cpp ../common/WizardLogger.hpp
	$(CXX) $(CXXFLAGS) -c ../common/WizardLogger.cpp

