#ifndef __MyDetectorConstructionGDML_h__
#define __MyDetectorConstructionGDML_h__

#include "G4Box.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"

class MyDetectorConstructionGDML : public G4VUserDetectorConstruction{

  public:
    MyDetectorConstructionGDML(){}
    ~MyDetectorConstructionGDML(){}

    G4VPhysicalVolume* Construct(){
    
      
      G4GDMLParser parser;

      parser.Read("simplegeometry.gdml");


      G4VPhysicalVolume *fWorld = parser.GetWorldVolume();
      return fWorld;

    }

};

#endif
