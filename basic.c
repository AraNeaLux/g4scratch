// g++ -Wl,--copy-dt-needed-entries basic.c MyRunManager.cxx MyOutputManager.cxx `geant4-config --cflags --libs`

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

 runManager->BeamOn(10000);

 delete runManager; 


 return 0;
}
