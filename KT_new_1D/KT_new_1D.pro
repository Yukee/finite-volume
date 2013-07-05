TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    cell.cpp \
    limiter.cpp \
    copycell.cpp \
    timesolver.cpp \
    cellarray.cpp \
    lxf.cpp \
    spatialsolver.cpp \
    function.cpp \
    lin.cpp \
    const.cpp \
    nt.cpp \
    staggeredcell.cpp \
    burgers.cpp \
    kt1.cpp \
    kt2.cpp

HEADERS += \
    cell.h \
    limiter.h \
    copycell.h \
    timesolver.h \
    cellarray.h \
    spatialsolver.h \
    lxf.h \
    function.h \
    lin.h \
    const.h \
    nt.h \
    staggeredcell.h \
    burgers.h \
    kt1.h \
    kt2.h

