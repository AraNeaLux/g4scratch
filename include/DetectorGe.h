#ifndef __DETECTORGE_H__
#define __DETECTORGE_H__

class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorGe {
  public:
    DetectorGe(G4LogicalVolume *parent, double radius, double angle); 
    ~DetectorGe();

    G4VPhysicalVolume *Construct();
    
    //G4LogicalVolume    *GetLogical()   { return fDetectorGeLogic;  }
    //G4VPhysicalVolume  *GetPhysical()  { return fDetectorGePhysical; }

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
