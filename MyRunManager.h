#ifndef __MyRunManager_h__
#define __MyRunManager_h__

#include "G4RunManager.hh"
#include <iostream>

class MyRunManager : public G4RunManager{
  public: 
    MyRunManager():G4RunManager(){}
    ~MyRunManager(){}

    void AnalyzeEvent (G4Event *anEvent){
      std::cout << "i am very LOUD" << std::endl;

      anEvent->Print();


    };



};

#endif
