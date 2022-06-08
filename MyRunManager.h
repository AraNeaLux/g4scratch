#ifndef __MyRunManager_h__
#define __MyRunManager_h__

#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "G4UserEventAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4Run.hh"
#include <iostream>
#include <fstream>

class MyRunManager : public G4RunManager{
  public: 
    MyRunManager();
    ~MyRunManager();


    void AnalyzeEvent (G4Event *anEvent);
    
};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MyRunAction : public G4UserRunAction {
  public:
    MyRunAction();
    ~MyRunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    std::ofstream ofile;

};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MyEventAction : public G4UserEventAction {
  public:
    MyEventAction();
    ~MyEventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MySteppingAction : public G4UserSteppingAction {
  public:
    MySteppingAction();
    ~MySteppingAction();

    void UserSteppingAction(const G4Step*);
};





#endif
