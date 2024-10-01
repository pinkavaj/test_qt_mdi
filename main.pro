CONFIG += debug
QT += widgets
SOURCES += main.cpp
QMAKE_CXXFLAGS_DEBUG += -ggdb3 -Og -mtune=native -march=x86-64-v2
