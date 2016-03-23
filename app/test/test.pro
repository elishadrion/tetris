TARGET = run_tests
QT -= gui
TEMPLATE = app
#HEADERS = *.hpp
SOURCES = *.cpp
OBJECTS += $${top}/server/tmp/Player.o \
	   $${top}/server/tmp/PlayerManager.o \
	   $${top}/server/tmp/Collection.o \
	   $${top}/server/tmp/Deck.o \
	   $${top}/server/tmp/Card.o \
	   $${top}/server/tmp/Connection.o \
	   $${top}/server/tmp/PacketManager.o \
	   $${top}/server/tmp/PlayerConnect.o \
	   $${top}/server/tmp/PlayerInGame.o \
	   $${top}/server/tmp/CardManager.o \
	   $${top}/server/tmp/CardMonster.o \
	   $${top}/server/tmp/Game.o \
	   $${top}/server/tmp/Effect.o \
	   # $${top}/server/tmp/.o \
	   # $${top}/server/tmp/.o

DESTDIR = $${top}

OTHER_FILES +=
