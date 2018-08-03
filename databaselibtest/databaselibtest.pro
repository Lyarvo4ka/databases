include(gtest_dependency.pri)

#CONFIG -= qt
QT       += sql
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS += \
    test_sqlquery.h

SOURCES += \
        main.cpp
