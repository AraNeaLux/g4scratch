#ifndef __EXPERIMENTCONSTUCTION_H__
#define __EXPERIMENTCONSTUCTION_H__

#include <G4VUserDetectorConstruction.hh>

class G4VPhysicalVolume;
class ExperimentalHall;

class ExperimentConstruction : public G4VUserDetectorConstruction {
  public:
    ExperimentConstruction();  
    ~ExperimentConstruction();  
    
    virtual G4VPhysicalVolume *Construct();

    void ConstructSDandField();

    void writeGDML(std::string oname="experiment.gdml");

    ExperimentalHall *GetHall() { return fExpHall; } 

  private:
     ExperimentalHall *fExpHall;
    

};


#endif
