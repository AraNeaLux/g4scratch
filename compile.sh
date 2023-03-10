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
g++ $CFLAGS basic.c $SRC $INC $GFLAGS $LIBS $(root-config --cflags --libs) -ltbb

#g++ -Wl,--copy-dt-needed-entries basic.c $SRC -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4INTY_USE_QT -DG4UI_USE_QT -DG4VIS_USE_OPENGLQT -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include/QtOpenGL -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -pipe -DG4USE_STD11 -pthread -ftls-model=initial-exec -std=c++11 -DG4MULTITHREADED -I/opt/geant4.10.05-install/bin/../include/Geant4  `geant4-config --libs` `root-config --cflags --libs` -ltbb
