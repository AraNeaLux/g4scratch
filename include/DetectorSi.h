#ifndef __DETECTORSI_H__
#define __DETECTORSI_H__

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

#endif
