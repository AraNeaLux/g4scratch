#ifndef __MyHit_h__
#define __MyHit_h__

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

class MyHit : public G4VHit{
  public: 
    MyHit() : G4VHit(), 
    fPos(G4ThreeVector()),
    fEdep(0.),
    fChamberNb(-1){

    };

    ~MyHit(){
    };

    virtual void Print(){
      G4cout << "position: \t" << G4BestUnit(fPos, "Length") << G4endl;
      G4cout << "edep: \t" << G4BestUnit(fEdep, "Energy") << G4endl;
      G4cout << "ChamberNb: \t" << fChamberNb << G4endl;
    };
   
    G4ThreeVector fPos;
    double fEdep;
    int fChamberNb;

    void SetPos(G4ThreeVector xyz) {fPos=xyz; };
    void SetEdep(double edep) {fEdep = edep;};
    void SetChamberNb(int chamberNb) {fChamberNb = chamberNb;};

    G4ThreeVector GetPos() {return fPos; };
    double GetEdep() {return fEdep; };
    int GetChamberNb() {return fChamberNb; };
    
    


};

typedef G4THitsCollection<MyHit> MyTrackerHitsCollection;



#endif
