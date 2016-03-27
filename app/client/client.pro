TARGET = client_wizard
QT += widgets
TEMPLATE = app
HEADERS = *.hpp CLI/*.hpp GUI/*.hpp
SOURCES = *.cpp CLI/*.cpp GUI/*.cpp
DESTDIR = $${top}

OTHER_FILES +=

#RESOURCES += images.qrc
