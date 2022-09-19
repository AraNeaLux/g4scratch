#ifndef __MyHit_h__
#define __MyHit_h__

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

class MyHit : public G4VHit{
  public: 
    MyHit();
    ~MyHit();

    virtual void Print();
    
    G4ThreeVector fPos;

    void SetPos(G4ThreeVector xyz) {fPos=xyz; };

    G4ThreeVector GetPos() {return fPos; };
       
    


};

typedef G4THitsCollection<MyHit> MyTrackerHitsCollection;



#endif
