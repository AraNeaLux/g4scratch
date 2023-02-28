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

    G4VPhysicalVolume* Construct(){

      G4Box* solidWorld = new G4Box("World",
                                    10*cm,10*cm,10*cm);
      G4Box* solidTarget = new G4Box("Target",
                                     5*cm, 5*cm, 5*cm);
   
      // Pointer to Geant4's materials database
      G4NistManager* nist = G4NistManager::Instance();
   
      // Make Lead and Air materials from database
      G4Material* Pb =  nist->FindOrBuildMaterial("G4_Pb");
      G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
      
      // Make the world air and the target lead
      G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, 
                                                        air, "myWorld");
      G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, 
                                                         Pb, "myTarget");

      // Place world
      G4VPhysicalVolume* physWorld = new G4PVPlacement(
            0,                  //no rotation
            G4ThreeVector(),    //at (0,0,0)
            logicWorld,         //its logical volume
            "World",            //its name
            0,                  //its mother  volume
            false,                      //no boolean operation
            0,                  //copy number
            true);                      //overlaps checking 

       // Place target
       G4VPhysicalVolume* physTarget = new G4PVPlacement(
            0,                  //no rotation
            G4ThreeVector(),    //at (0,0,0)
            logicTarget,         //its logical volume
            "Target",           //its name
            logicWorld,         //its mother  volume
            false,                      //no boolean operation
            0,                  //copy number
            true);                      //overlaps checking 

        return physWorld;

    }

};

#endif
