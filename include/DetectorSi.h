#ifndef __DETECTORSI_H__
#define __DETECTORSI_H__

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorSi {
  public:
    DetectorSi(G4LogicalVolume *parent, double radius, double angle); 
    ~DetectorSi();

    G4VPhysicalVolume *Construct();
    
    //G4LogicalVolume    *GetLogical()   { return fDetectorSiLogic;  }
    //G4VPhysicalVolume  *GetPhysical()  { return fDetectorSiPhysical; }

  private:
    G4LogicalVolume *fParent;
    double fRadius;
    double fAngle;
    int fCopyNum;
    double fCrystRad;
    double fCrystZ;
    static int fCopyCounter;

};


/// Sensitive detector to be attached to the GDML geometry

class TrackerSiSD : public G4VSensitiveDetector{
  public:
      TrackerSiSD(G4String const&);
     ~TrackerSiSD();

      virtual void Initialize(G4HCofThisEvent* hitCollection);
      virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
      virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
      MyTrackerHitsCollection* fHitsCollection;
};

#endif
