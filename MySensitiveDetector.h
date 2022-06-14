#ifndef __MySensitiveDetector_h__
#define __MySensitiveDetector_h__

#include "G4VSensitiveDetector.hh"

class G4Step;

/// Sensitive detector to be attached to the GDML geometry

class MySensitiveDetector : public G4VSensitiveDetector{
  public:
      MySensitiveDetector(const G4String&);
     ~MySensitiveDetector();

      virtual void Initialize(G4HCofThisEvent*);
      virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      virtual void EndOfEvent(G4HCofThisEvent*);
};
#endif
