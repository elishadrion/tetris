# Project layout and "modules"
TEMPLATE = subdirs
SUBDIRS = client server common
client.depends = common
server.depends = common
