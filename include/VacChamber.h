#ifndef __VACCHAMBER_H__
#define __VACCHAMBER_H__

class G4LogicalVolume;
class G4VPhysicalVolume;

class VacChamber {
  public:
    VacChamber(G4LogicalVolume *parent);
    ~VacChamber();

    G4VPhysicalVolume *Construct();
    
    //G4LogicalVolume    *GetLogical()   { return fVacChamberLogical;  }
    //G4VPhysicalVolume  *GetPhysical()  { return fVacChamberPhysical; }

  private:
    G4LogicalVolume *fParent;

};

#endif
