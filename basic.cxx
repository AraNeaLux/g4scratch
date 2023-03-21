
//#include "MyDetectorConstructionGDML.h"
#include "MyDetectorConstruction.h"
#include "MyPrimaryGeneratorAction.h"
#include "MyRunManager.h"
#include "MyPhysicsList.h"
#include "MySensitiveDetector.h"

#include "ExperimentConstruction.h"

#include <cstdio>
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "QGSP_BERT.hh"
#include "G4GDMLParser.hh"

#include "G4StepLimiterPhysics.hh"

int main(int argc, char **argv) {
  printf("hello\n");
  
  double energy = 500;
  std::string fName = "output";
  if (argc>1){
    energy = atof(argv[1]);
    std::string e(argv[1]);
    fName += e;
  }
  fName += ".root";

  //G4MTRunManager *runManager = new ....
  MyRunManager * runManager = new MyRunManager(fName);

//experimental setup
  ExperimentConstruction *experiment = new ExperimentConstruction();
  experiment->Construct();
  experiment->writeGDML();
  runManager->SetUserInitialization(experiment);
  

//physics list.... 
//  runManager->SetUserInitialization(new MyDetectorConstructionGDML(parser));
//  runManager->SetUserInitialization(new MyDetectorConstruction);
  //runManager->SetUserInitialization(new FTFP_BERT());
  //runManager->SetUserInitialization(new QBBC());
  //runManager->SetUserInitialization(new QGSP_BERT());
  G4VModularPhysicsList* physicsList = new MyPhysicsList();
  //physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
  

 
  runManager->SetUserAction(new MyPrimaryGeneratorAction(energy));
 
 // runManager->SetUserAction(/*  StackingAction   */);
 // runManager->SetUserAction(/*  RunAction   */);
  runManager->SetUserAction(new MyRunAction());
 // runManager->SetUserAction(/*  EventAction   */);
  runManager->SetUserAction(new MyEventAction());
 // runManager->SetUserAction(/*  TrackingAction   */);
 // runManager->SetUserAction(/*  SteppingAction   */);
  runManager->SetUserAction(new MySteppingAction());
  //runManager->SetUserAction(new MyTrackingAction());


  std::cout << " I AM HERE 1" << std::endl;
 
  runManager->Initialize();

  std::cout << " I AM HERE 2" << std::endl;

 
  if(argc<2) {
    runManager->BeamOn(10000);
  } else {
    int iterations = atoi(argv[1]);
    runManager->BeamOn(iterations);
  }
 

  delete runManager; 
 
 
  return 0;
}
