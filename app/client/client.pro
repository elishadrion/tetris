TARGET = client_wizard
QT += widgets
TEMPLATE = app
HEADERS = *.hpp CLI/*.hpp GUI/*.hpp \
    GUI/GameGUI.h
SOURCES = *.cpp CLI/*.cpp GUI/*.cpp \
    GUI/GameGUI.cpp
DESTDIR = $${top}
