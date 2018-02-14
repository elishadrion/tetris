cd client/
make -f Makefile_client 
rm *.o
cd ../game
rm *.o
cd ../server
bash compile.sh
