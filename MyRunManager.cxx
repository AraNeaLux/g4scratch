#include "MyRunManager.h"
#include "MyOutputManager.h"
#include "MyDetectorConstructionGDML.h"

#include "G4SystemOfUnits.hh"

#include <cstdio>
#include <fstream>

//#include <TFile.h>

std::fstream logfile;

void writeToLog(const char* text,int rewrite = 0){
  if (rewrite != 0) {
    logfile.open("junk.log", std::fstream::out);
    logfile << text <<G4endl;
    logfile.close();
  }
  else {
    logfile.open("junk.log", std::fstream::out | std::fstream::app);
    logfile << text <<G4endl;
    logfile.close();
  }
}

std::fstream datfile;



MyRunManager::MyRunManager():G4RunManager(){
  //printf("MyRunManager created\n");
  writeToLog("--- BEGIN OF RUN ---",1);

  MyOutputManager::Get()->setupTree();

}

MyRunManager::~MyRunManager(){
  //printf("MyRunManager destroyed\n");
  writeToLog("--- END OF RUN ---");

  MyOutputManager::Get()->closeTree();

}


void MyRunManager::AnalyzeEvent (G4Event *anEvent){


  //std::cout << "i am very LOUD" << std::endl;

  //anEvent->Print();
}


// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...


MyRunAction::MyRunAction():G4UserRunAction(){
  //printf("MyRunAction created\n");
  writeToLog("MyRunAction created");
}

MyRunAction::~MyRunAction(){
  //ofile << G4endl << "MyRunAction destroyed" << G4endl;
  writeToLog("MyRunAction destroyed");
}

void MyRunAction::BeginOfRunAction(const G4Run*){
//  printf("%s\n",__PRETTY_FUNCTION__);
//  fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

void MyRunAction::EndOfRunAction(const G4Run*){
  //printf("%s\n",__PRETTY_FUNCTION__);
  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...


MyEventAction::MyEventAction():G4UserEventAction(){
  //printf("MyEventAction created\n");
  writeToLog("MyEventAction created");
}

MyEventAction::~MyEventAction(){
  //printf("MyEventAction destroyed\n");
  writeToLog("MyEventAction destoyed");
}

void MyEventAction::BeginOfEventAction(const G4Event*){
  //printf("%s\n",__PRETTY_FUNCTION__);
  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

void MyEventAction::EndOfEventAction(const G4Event* event){

  double xPrimary = event->GetPrimaryVertex()->GetX0()/cm;
  double yPrimary = event->GetPrimaryVertex()->GetY0()/cm;
  double zPrimary = event->GetPrimaryVertex()->GetZ0()/cm;


  //printf("PRIMARY: %.02f\t %.02f\t %.02f\n",xPrimary,yPrimary,zPrimary);


  //printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);

}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

MySteppingAction::MySteppingAction():G4UserSteppingAction(){
  //printf("MySteppingAction created\n");
  writeToLog("MySteppingAction created");

  fEventID=-1;
  fParticleName="";
  fStepNum=-1;
  fSubStepNum=-1;
  fProcess=-1;

datfile.open("junk.dat");
  datfile << "EventID/I:"
          << "particle/C:"
          //<< "stepnum/I:"
          << "px/D:"
          << "py/D:"
          << "pz/D" << G4endl;
//          TH1D h("h","h",100,0,100);

}

MySteppingAction::~MySteppingAction(){
  //printf("MySteppingAction destroyed\n");
  writeToLog("MySteppingAction destroyed");
  datfile.close();

}

void MySteppingAction::UserSteppingAction(const G4Step* step){

  G4Track *track = step->GetTrack();
  G4String partname = track->GetParticleDefinition()->GetParticleName();

  fParticleName = partname;

/*
  if(fEventID!=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID()){
    // do something useful
    fParticleName = partname;
    fStepNum = 0;
    fSubStepNum = 0;
    fEventID=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  } else {
    fStepNum++;
    if(fParticleName.compare(partname)!= 0){ // current particle not prev particle
      fSubStepNum = 0;
      fParticleName = partname;
    } else {
      fSubStepNum++;
    }
  }
*/

  // EVENT ID THINGS
  fEventID=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // TRACK ID THINGS
  int fTrackID = track->GetTrackID();

  // STEP ID THINGS
  int fStepNum = track->GetCurrentStepNumber();

  // SECONDARIES
  const std::vector<const G4Track*> *substep = step->GetSecondaryInCurrentStep();
  for (unsigned int i = 0; i < substep->size(); ++i){
    int sectrackid = (*step->GetSecondaryInCurrentStep())[i]->GetTrackID();
    std::vector<int> secondaries;
    secondaries.push_back(sectrackid);

//    for (int x : secondaries)
//      G4cout << x << G4endl;
  }
  


  // VOLUME THINGS
  G4VPhysicalVolume *stepvol = step->GetPreStepPoint()->GetPhysicalVolume();

//  printf(stepvol->GetName());
//  printf("\n");
/*
  if (stepvol == fWorld){
    printf("World\n");
  } else if (stepvol == myBlock_1){
    printf("Block\n");
  };
  
*/
  // ENERGY THINGS
  double ke = step->GetPostStepPoint()->GetKineticEnergy();
  double edep = step->GetTotalEnergyDeposit();

  // PROCESS THINGS
  std::string processname 
    = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  if (processname=="Transportation"){fProcess = 0;}
  else if (processname=="UserMaxStep"){fProcess = 1;}
  else if (processname=="hIoni"){fProcess = 2;}
  else if (processname=="CoulombScat"){fProcess = 3;}
  else if (processname=="ionIoni"){fProcess = 4;}
  else if (processname=="hadElastic"){fProcess = 5;}
  else {fProcess=19375;
    G4cout << processname << G4endl;
  };


/*  datfile << MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID() 
          << "\t" << partname
          << "\t" << x
          << "\t" << y
          << "\t" << z << G4endl;
*/

  // POSITIONY THINGS
  //step->GetPreStepPoint()->GetPosition();

  G4ThreeVector presteppos = step->GetPreStepPoint()->GetPosition()*cm;
  G4ThreeVector poststeppos = step->GetPostStepPoint()->GetPosition()*cm;

  float x = poststeppos.x()/cm;
  float y = poststeppos.y()/cm;
  float z = poststeppos.z()/cm;

  float xdep = x; 

  G4ThreeVector shift = presteppos + G4UniformRand()*(poststeppos - presteppos);
  if (step->GetTrack()->GetDefinition()->GetPDGCharge()==0.) shift = presteppos;
  xdep = shift.x()/cm;


  //printf("%s\n",__PRETTY_FUNCTION__);

  //printf("steplength = %.02f nm\n",steplength);
  //printf(partname);
  //printf("\n %.02f\t %.02f\t %.02f\n",x,y,z);


  MyOutputManager::Get()->fill(fEventID,fTrackID,fStepNum,fSubStepNum,fParticleName,fProcess,ke/keV,edep/keV,x/um,xdep/um,y/um,z/um);

  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
