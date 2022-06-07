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

