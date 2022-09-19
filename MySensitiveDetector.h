#ifndef __MySensitiveDetector_h__
#define __MySensitiveDetector_h__

#include "G4VSensitiveDetector.hh"
#include "MyHit.h"

class G4Step;
class G4HCofThisEvent;

/// Sensitive detector to be attached to the GDML geometry

class MySensitiveDetector : public G4VSensitiveDetector{
  public:
      MySensitiveDetector(const G4String& name, 
                          const G4String& hitsCollectionName);
     ~MySensitiveDetector();

      virtual void Initialize(G4HCofThisEvent* hitCollection);
      virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
      virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

      MyTrackerHitsCollection* fHitsCollection;
};
#endif
