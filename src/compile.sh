g++ -c User.cpp -o User.o
g++ -std=c++17 -c server.cpp -o server.o
g++ -std=c++17 -pthread /home/prout/Desktop/Group2/src/dependencies/CSVparser/CSVparser.cpp User.o server.o servert.cpp -o servert
g++ -std=c++17 -c Client.cpp -o Client.o
g++ -std=c++17 -pthread Client.o clientt.cpp -o clientt
rm *.o *.out


