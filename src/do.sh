cd client/
make -f Makefile_client
cd ../server
make -f Makefile_server
rm *.o
cd ../client
rm *.o
cd ../game
rm *.o
