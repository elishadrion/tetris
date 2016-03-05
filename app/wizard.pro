# Project layout and "modules"
CONFIG += qt
TEMPLATE = subdirs
SUBDIRS = client server common
client.depends = common
server.depends = common
