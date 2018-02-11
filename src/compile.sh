g++ -c User.cpp -o User.o
g++ -std=c++17 -c server.cpp -o server.o
g++ -std=c++17 -c List.cpp -o List.o
g++ -std=c++17 -pthread /home/prout/Desktop/Group2/src/dependencies/CSVparser/CSVparser.cpp User.o List.o server.o servert.cpp -o servert
rm *.o *.out


