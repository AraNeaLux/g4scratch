#ifndef __MyDetectorConstruction_h__
#define __MyDetectorConstruction_h__

#include "G4Box.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction{

  public:
    MyDetectorConstruction(){}
    ~MyDetectorConstruction(){}

    G4VPhysicalVolume* Construct();

};

#endif
