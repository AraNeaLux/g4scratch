#!/bin/bash

SRC=" src/MyRunManager.cxx src/MyOutputManager.cxx src/MySensitiveDetector.cxx "

G4PREFIX=$(geant4-config --prefix)
CFLAGS=$(geant4-config --cflags)
GFFLAGS=" "

LIBS=$(geant4-config --libs)
LIBS+=" -lxerces-c"


INC=" -I/usr/include/QtCore "
INC+=" -I/usr/include/QtGui "
INC+=" -I/usr/include/QtOpenGL "
INC+=" -I$G4PREFIX/include/Geant4 "
INC+=" -I./include "


echo g++ $CFLAGS basic.c $SRC $INC $GFLAGS $LIBS $(root-config --cflags --libs) -ltbb
g++ $CFLAGS basic.cxx $SRC $INC $GFLAGS $LIBS $(root-config --cflags --libs) -ltbb

