TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    databaselib \
    databaseapp \
    databaselibtest

databaseapp.depends = databaselib
