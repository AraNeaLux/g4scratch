#ifndef __MyHit_h__
#define __MyHit_h__

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

class MyHit : public G4VHit{
  public: 
    MyHit() : G4VHit(), fPos(G4ThreeVector()) {

    };

    ~MyHit(){
    };

    virtual void Print(){
      G4cout << "position: " << G4BestUnit(fPos, "Length") << G4endl;
    };
   
    G4ThreeVector fPos;

    void SetPos(G4ThreeVector xyz) {fPos=xyz; };

    G4ThreeVector GetPos() {return fPos; };
    
    


};

typedef G4THitsCollection<MyHit> MyTrackerHitsCollection;



#endif
