// g++ basic.c `geant4-config --cflags --libs`
#include "MyDetectorConstruction.h"
#include "MyPrimaryGeneratorAction.h"
#include "MyRunManager.h"

#include <cstdio>
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"

int main() {
 printf("hello\n");
 
 MyRunManager * runManager = new MyRunManager;

 runManager->SetUserInitialization(new MyDetectorConstruction());
 runManager->SetUserInitialization(new FTFP_BERT());
 runManager->SetUserAction(new MyPrimaryGeneratorAction());

 runManager->Initialize();

 runManager->BeamOn(10);

 delete runManager; 


 return 0;
}
