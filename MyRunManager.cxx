#include "MyRunManager.h"

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
}

MyRunManager::~MyRunManager(){
  //printf("MyRunManager destroyed\n");
  writeToLog("--- END OF RUN ---");
}


void MyRunManager::AnalyzeEvent (G4Event *anEvent){


  std::cout << "i am very LOUD" << std::endl;

  anEvent->Print();
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
  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
}

void MyRunAction::EndOfRunAction(const G4Run*){
  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
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
  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
}

void MyEventAction::EndOfEventAction(const G4Event* event){

  double xPrimary = event->GetPrimaryVertex()->GetX0();
  double yPrimary = event->GetPrimaryVertex()->GetY0();
  double zPrimary = event->GetPrimaryVertex()->GetZ0();


  printf("PRIMARY: %.02f\t %.02f\t %.02f\n",xPrimary,yPrimary,zPrimary);


  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);

}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

MySteppingAction::MySteppingAction():G4UserSteppingAction(){
  //printf("MySteppingAction created\n");
  writeToLog("MySteppingAction created");


datfile.open("junk.dat");
  datfile << "EventID/I:"
          << "particle/C:"
          //<< "stepnum/I:"
          << "x/D:"
          << "y/D:"
          << "z/D" << G4endl;
//          TH1D h("h","h",100,0,100);

}

MySteppingAction::~MySteppingAction(){
  //printf("MySteppingAction destroyed\n");
  writeToLog("MySteppingAction destroyed");
  datfile.close();

}

void MySteppingAction::UserSteppingAction(const G4Step* step){
  //step->GetPreStepPoint()->GetPosition();
  G4ThreeVector steppos = step->GetPostStepPoint()->GetPosition();
  double x = steppos.x();
  double y = steppos.y();
  double z = steppos.z();

  //double steplength = step->GetStepLength();

  G4Track *track = step->GetTrack();
  G4String partname = track->GetParticleDefinition()->GetParticleName();


  printf("%s\n",__PRETTY_FUNCTION__);

  //printf("steplength = %.02f nm\n",steplength);
  printf(partname);
  printf("\n %.02f\t %.02f\t %.02f\n",x,y,z);

  x = round( x * 1000.0 ) / 1000.0;
  y = round( y * 1000.0 ) / 1000.0;
  z = round( z * 1000.0 ) / 1000.0;

  datfile << MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID() 
          << "\t" << partname
          << "\t" << x
          << "\t" << y
          << "\t" << z << G4endl;


  fflush(stdout);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
