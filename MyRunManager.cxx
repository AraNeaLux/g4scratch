#include "MyRunManager.h"
#include "MyOutputManager.h"

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

  double xPrimary = event->GetPrimaryVertex()->GetX0()*cm;
  double yPrimary = event->GetPrimaryVertex()->GetY0()*cm;
  double zPrimary = event->GetPrimaryVertex()->GetZ0()*cm;


  printf("PRIMARY: %.02f\t %.02f\t %.02f\n",xPrimary,yPrimary,zPrimary);


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

  // TRACK ID THINGS
  int fTrackID = track->GetTrackID();


  // POSITIONY THINGS
  //step->GetPreStepPoint()->GetPosition();
  G4ThreeVector steppos = step->GetPostStepPoint()->GetPosition();
  double x = steppos.x();
  double y = steppos.y();
  double z = steppos.z();

  //double steplength = step->GetStepLength();



  //printf("%s\n",__PRETTY_FUNCTION__);

  //printf("steplength = %.02f nm\n",steplength);
  //printf(partname);
  //printf("\n %.02f\t %.02f\t %.02f\n",x,y,z);

  // ENERGY THINGS
  double ke = step->GetPostStepPoint()->GetKineticEnergy();

/*  datfile << MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID() 
          << "\t" << partname
          << "\t" << x
          << "\t" << y
          << "\t" << z << G4endl;
*/

  MyOutputManager::Get()->fill(fEventID,fTrackID,fStepNum,fSubStepNum,fParticleName,ke,x,y,z);

  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
