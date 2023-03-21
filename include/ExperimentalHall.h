#ifndef __EXPERIMENTALHALL__
#define __EXPERIMENTALHALL__


class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;

class ExperimentalHall {
  public:
    ExperimentalHall();
    ~ExperimentalHall();

    virtual G4VPhysicalVolume *Construct();

    void SetXYZ(double x, double y, double z);

    G4LogicalVolume    *GetLogical()   { return fExpHallLogical;  }
    G4VPhysicalVolume  *GetPhysical()  { return fExpHallPhysical; }

  private:
    double fExpHallX;
    double fExpHallY;
    double fExpHallZ;

    G4Box              *fExpHall;
    G4LogicalVolume    *fExpHallLogical;
    G4VPhysicalVolume  *fExpHallPhysical;

}; 


#endif



