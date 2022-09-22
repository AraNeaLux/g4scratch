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
/*
      G4LogicalVolume *fblock = fParser.GetVolume("myBlock");
      G4double maxStep = 0.000001;
      G4UserLimits *fStepLimit = new G4UserLimits(maxStep);
      fblock->SetUserLimits(fStepLimit);
*/
      G4cout << "Made World" << G4endl;
      return fWorld;
    }

    void ConstructSDandField(){
      G4SDManager *SDman = G4SDManager::GetSDMpointer();

      G4String SDname = "detector";
      G4String HCname = "HitsCollectionName";
      MySensitiveDetector* aSD = new MySensitiveDetector(SDname,HCname);
      SDman->AddNewDetector(aSD);

      G4cout << "Added new SD" << G4endl;


      G4String volname = "myDetector";
      G4LogicalVolume *fdet = fParser.GetVolume(volname);
      fdet->SetSensitiveDetector(aSD);

      G4cout << "Added " << volname << G4endl;

    }


};

#endif
