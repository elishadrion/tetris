g++ -c User.cpp -o User.o
g++ -std=c++17 -c Server.cpp -o Server.o
g++ -std=c++17 -c Room.cpp -o Room.o
g++ -std=c++17 -pthread /home/prout/Desktop/Group2/src/dependencies/CSVparser/CSVparser.cpp User.o ../game/Game.o Room.o Server.o servert.cpp -o servert
rm *.o *.out


