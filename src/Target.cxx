
#include "Target.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Box.hh>


#include <G4NistManager.hh>


Target::Target(G4LogicalVolume *parent) : fParent(parent) {

}

Target::~Target() { } 

G4VPhysicalVolume *Target::Construct() {
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* Ta  = nist->FindOrBuildMaterial("G4_Ta");
  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*CLHEP::g/CLHEP::mole;
  G4double density = 1.e-25*CLHEP::g/CLHEP::cm3;
  G4double temperature = 2.73*CLHEP::kelvin;
  G4double pressure = 3.e-18*CLHEP::pascal;
  G4Material* vacuum = new G4Material("interGalactic", atomicNumber,
                                       massOfMole, density, kStateGas,
                                       temperature, pressure);


  //G4Box *target = new G4Box("target",1.*CLHEP::cm,1.*CLHEP::cm,0.1*CLHEP::cm);
  G4Box *target = new G4Box("target",10.*CLHEP::cm,10.*CLHEP::cm,10.*CLHEP::cm);
  //G4LogicalVolume *targetLogical = new G4LogicalVolume(target,Materials::Get("Ta"),"target_L");//,0,0,0);  
  G4LogicalVolume *targetLogical = new G4LogicalVolume(target,Ta,"target_L");//,0,0,0);  
  //TODO set user limits

  G4VPhysicalVolume *targetPhysical = new G4PVPlacement(
                                      0,               // no rotation
                                      G4ThreeVector(1000,1000,1000), // at (0,0,0)
                                      targetLogical,   // its logical volume
                                      "target_P",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      0,               // copy number
                                      true);           // overlap checking

  return targetPhysical;
}

