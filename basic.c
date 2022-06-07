// g++ -Wl,--copy-dt-needed-entries basic.c `geant4-config --cflags --libs`
#include "MyDetectorConstruction.h"
#include "MyPrimaryGeneratorAction.h"
#include "MyRunManager.h"

#include <cstdio>
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"

#include "G4GDMLParser.hh"

int main() {
 printf("hello\n");
 
 G4GDMLParser parser;

 parser.Read("simplegeometry.gdml");


 MyRunManager * runManager = new MyRunManager;

 runManager->SetUserInitialization(new MyDetectorConstruction());
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
