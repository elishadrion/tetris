g++ -c User.cpp -o User.o
g++ -std=c++17 -c Server.cpp -o Server.o
g++ -std=c++17 -c LinkedList.cpp -o LinkedList.o
g++ -std=c++17 -pthread /home/prout/Desktop/Group2/src/dependencies/CSVparser/CSVparser.cpp User.o LinkedList.o Server.o servert.cpp -o servert
rm *.o *.out


