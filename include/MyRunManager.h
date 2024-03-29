#ifndef __MyRunManager_h__
#define __MyRunManager_h__

#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "G4UserEventAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserTrackingAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>




class MyRunManager : public G4RunManager{
  public: 
    MyRunManager(std::string fName = "output.root");
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

//    std::ofstream ofile;
};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MyEventAction : public G4UserEventAction {
  public:
    MyEventAction();
    ~MyEventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
//    std::ofstream ofile;
};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MySteppingAction : public G4UserSteppingAction {
  public:
    MySteppingAction();
    ~MySteppingAction();

    void UserSteppingAction(const G4Step*);
    std::ofstream datfile;

    long fEventID;
    std::string fParticleName;
    long fProcess;
    long fStepNum;
    double fStepLen;
    long fVolume;

};

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

class MyTrackingAction : public G4UserTrackingAction {
  public:
    MyTrackingAction();
    ~MyTrackingAction();

    void PreUserTrackingAction(const G4Track*);
    void PostUserTrackingAction(const G4Track*);
};

#endif
