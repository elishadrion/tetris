TARGET = server_wizard
TEMPLATE = app
QT -= gui core # Don't need QT for server
HEADERS = ../common/Constants.hpp \
          ../common/Error.hpp \
          ../common/Packet.hpp \
          ../common/WizardLogger.hpp \
          *.hpp
SOURCES = ../common/WizardLogger.cpp \
          *.cpp

## Intermediary files
OBJECTS_DIR = ./server-tmp
MOC_DIR = ./server-tmp
