// g++ -Wl,--copy-dt-needed-entries basic.c MyRunManager.cxx MyOutputManager.cxx `geant4-config --cflags --libs`


// g++ -Wl,--copy-dt-needed-entries basic.c MyRunManager.cxx MyOutputManager.cxx -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4INTY_USE_QT -DG4UI_USE_QT -DG4VIS_USE_OPENGLQT -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include/QtOpenGL -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -pipe -DG4USE_STD11 -pthread -ftls-model=initial-exec -std=c++11 -DG4MULTITHREADED -I/opt/geant4.10.05-install/bin/../include/Geant4  `geant4-config --libs` `root-config --cflags --libs` -ltbb

#include "MyDetectorConstructionGDML.h"
//#include "MyDetectorConstruction.h"
#include "MyPrimaryGeneratorAction.h"
#include "MyRunManager.h"
#include "MyPhysicsList.h"

#include <cstdio>
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "QGSP_BERT.hh"
#include "G4GDMLParser.hh"

#include "G4StepLimiterPhysics.hh"

int main(int argc, char **argv) {
  printf("hello\n");
  
  G4GDMLParser parser;
  parser.Read("simplegeometry.gdml");
 
  MyRunManager * runManager = new MyRunManager;
 
  runManager->SetUserInitialization(new MyDetectorConstructionGDML(parser));
  //runManager->SetUserInitialization(new MyDetectorConstruction);
  //runManager->SetUserInitialization(new FTFP_BERT());
  //runManager->SetUserInitialization(new QBBC());
  //runManager->SetUserInitialization(new QGSP_BERT());

  G4VModularPhysicsList* physicsList = new MyPhysicsList();
  //physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
  
 
  runManager->SetUserAction(new MyPrimaryGeneratorAction());
 
 // runManager->SetUserAction(/*  StackingAction   */);
 // runManager->SetUserAction(/*  RunAction   */);
  runManager->SetUserAction(new MyRunAction());
 // runManager->SetUserAction(/*  EventAction   */);
  runManager->SetUserAction(new MyEventAction());
 // runManager->SetUserAction(/*  TrackingAction   */);
 // runManager->SetUserAction(/*  SteppingAction   */);
  runManager->SetUserAction(new MySteppingAction());
  //runManager->SetUserAction(new MyTrackingAction());
 
  runManager->Initialize();
 
  if(argc<2) {
    runManager->BeamOn(100000);
  } else {
    int iterations = atoi(argv[1]);
    runManager->BeamOn(iterations);
  }
 

  delete runManager; 
 
 
  return 0;
}
