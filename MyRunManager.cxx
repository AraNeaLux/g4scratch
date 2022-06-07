#include "MyRunManager.h"
#include <cstdio>

MyRunManager::MyRunManager():G4RunManager(){
  printf("MyRunManager created\n");

}

MyRunManager::~MyRunManager(){
  printf("MyRunManager destroyed\n");

}


void MyRunManager::AnalyzeEvent (G4Event *anEvent){


  std::cout << "i am very LOUD" << std::endl;

  anEvent->Print();
};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...


MyRunAction::MyRunAction():G4UserRunAction(){
  printf("MyRunAction created\n");

}

MyRunAction::~MyRunAction(){
  printf("MyRunAction destroyed\n");

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
  printf("MyEventAction created\n");

}

MyEventAction::~MyEventAction(){
  printf("MyEventAction destroyed\n");

}

void MyEventAction::BeginOfEventAction(const G4Event*){
  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
}

void MyEventAction::EndOfEventAction(const G4Event* event){

  double x = event->GetPrimaryVertex()->GetX0();
  double y = event->GetPrimaryVertex()->GetY0();
  double z = event->GetPrimaryVertex()->GetZ0();

  printf("%.02f\t %.02f\t %.02f\n",x,y,z);


  printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);

}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

MySteppingAction::MySteppingAction():G4UserSteppingAction(){
  printf("MySteppingAction created\n");

}

MySteppingAction::~MySteppingAction(){
  printf("MySteppingAction destroyed\n");

}

void MySteppingAction::UserSteppingAction(const G4Step* step){
  //step->GetPreStepPoint()->GetPosition();
  //step->GetPostStepPoint()->GetPosition();

  double steplength = step->GetStepLength();



  printf("%s\n",__PRETTY_FUNCTION__);

  printf("steplength = %.02f\n",steplength);

  fflush(stdout);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
