TARGET = client_wizard
QT += widgets
TEMPLATE = app
HEADERS = ../common/Constants.hpp \
          ../common/Error.hpp \
          ../common/Packet.hpp \
          ./CLI/CLIPanel.hpp \
          ./CLI/CollectionPanel.hpp \
          ./CLI/DeckPanel.hpp \
          ./CLI/FriendPanel.hpp \
          ./CLI/GamePanel.hpp \
          ./CLI/LoginPanel.hpp \
          ./CLI/MainPanel.hpp \
          ./CLI/TchatPanel.hpp \
          ./CLI/WaitPanel.hpp \
          ./GUI/LoginPanel.hpp \
          *.hpp
SOURCES = ../common/WizardLogger.cpp \
          ./CLI/CollectionPanel.cpp \
          ./CLI/DeckPanel.cpp \
          ./CLI/FriendPanel.cpp \
          ./CLI/GamePanel.cpp \
          ./CLI/LoginPanel.cpp \
          ./CLI/MainPanel.cpp \
          ./CLI/TchatPanel.cpp \
          ./CLI/WaitPanel.cpp \
          ./GUI/LoginPanel.cpp \
          *.cpp

## Intermediary files
OBJECTS_DIR = ./client-tmp
MOC_DIR = ./client-tmp
