TARGET = client_wizard
QT += widgets
TEMPLATE = app
HEADERS = ../common/Constants.hpp \
          ../common/Error.hpp \
          ../common/Packet.hpp \
          ../common/WizardLogger.hpp \
          *.hpp
SOURCES = ../common/WizardLogger.cpp \
          *.cpp
