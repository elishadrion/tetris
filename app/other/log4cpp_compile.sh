#!/bin/sh

echo "Combien de job parallèle pour make ?"
read MAKE_JOBS

echo "Configuration pour cette machine"
cd log4cpp-src
mkdir build
cd build
../configure --prefix $PWD/package

echo "Compilation dans le dossier build avec $MAKE_JOBS jobs parallèles"
make -j $MAKE_JOBS

echo "Création de la librairies statique"
make install

echo "Copie de la librairie statique"
mkdir ../../../lib
mv package/lib/liblog4cpp.a ../../../lib/liblog4cpp.a

echo "DONE"
