#ifndef __MyDetectorConstructionGDML_h__
#define __MyDetectorConstructionGDML_h__

#include "MySensitiveDetector.h"

#include "G4Box.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4GDMLParser.hh"
#include "G4SDManager.hh"

#include "G4UserLimits.hh"

class G4GDMLParser;

class MyDetectorConstructionGDML : public G4VUserDetectorConstruction{

  const G4GDMLParser& fParser;

  public:
    MyDetectorConstructionGDML(const G4GDMLParser& parser)
     : G4VUserDetectorConstruction(),fParser(parser){
    }

    ~MyDetectorConstructionGDML(){}


    G4VPhysicalVolume* Construct(){

      G4VPhysicalVolume *fWorld = fParser.GetWorldVolume();

      G4LogicalVolume *fblock = fParser.GetVolume("myBlock");
      G4double maxStep = 0.01;
      G4UserLimits *fStepLimit = new G4UserLimits(maxStep);
      fblock->SetUserLimits(fStepLimit);

      return fWorld;
    }

    void ConstructSD(){
      G4SDManager *SDman = G4SDManager::GetSDMpointer();

      MySensitiveDetector* aSD = new MySensitiveDetector("detector");
      SDman->AddNewDetector(aSD);


      G4LogicalVolume *fdet = fParser.GetVolume("myDetector");
      fdet->SetSensitiveDetector(aSD);



    }


};

#endif
