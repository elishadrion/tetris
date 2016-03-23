# Project layout and "modules"
CONFIG += qt
TEMPLATE = subdirs
SUBDIRS = client server common test
client.depends = common
server.depends = common
test.depends = server client
