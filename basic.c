// g++ -Wl,--copy-dt-needed-entries basic.c MyRunManager.cxx MyOutputManager.cxx `geant4-config --cflags --libs`


// g++ -Wl,--copy-dt-needed-entries basic.c MyRunManager.cxx MyOutputManager.cxx -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4INTY_USE_QT -DG4UI_USE_QT -DG4VIS_USE_OPENGLQT -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include/QtOpenGL -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -pipe -DG4USE_STD11 -pthread -ftls-model=initial-exec -std=c++11 -DG4MULTITHREADED -I/opt/geant4.10.05-install/bin/../include/Geant4  `geant4-config --libs` `root-config --cflags --libs` -ltbb

#include "MyDetectorConstructionGDML.h"
#include "MyPrimaryGeneratorAction.h"
#include "MyRunManager.h"

#include <cstdio>
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"


int main() {
 printf("hello\n");
 


 MyRunManager * runManager = new MyRunManager;

 runManager->SetUserInitialization(new MyDetectorConstructionGDML());
 runManager->SetUserInitialization(new FTFP_BERT());

 runManager->SetUserAction(new MyPrimaryGeneratorAction());

// runManager->SetUserAction(/*  StackingAction   */);
// runManager->SetUserAction(/*  RunAction   */);
 runManager->SetUserAction(new MyRunAction());
// runManager->SetUserAction(/*  EventAction   */);
 runManager->SetUserAction(new MyEventAction());
// runManager->SetUserAction(/*  TrackingAction   */);
// runManager->SetUserAction(/*  SteppingAction   */);
 runManager->SetUserAction(new MySteppingAction());

 runManager->Initialize();

 runManager->BeamOn(10);

 delete runManager; 


 return 0;
}
