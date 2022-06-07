#ifndef __MyRunManager_h__
#define __MyRunManager_h__

#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include <iostream>

class MyRunManager : public G4RunManager{
  public: 
    MyRunManager();
    ~MyRunManager();


    void AnalyzeEvent (G4Event *anEvent);


};

class MyRunAction : public G4UserRunAction {
  public:
    MyRunAction();
    ~MyRunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);


};




#endif
