
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

  G4Box *target = new G4Box("target",1.*CLHEP::cm,1.*CLHEP::cm,10.*CLHEP::um);
  G4LogicalVolume *targetLogical = new G4LogicalVolume(target,Materials::Get("Ta"),"target_L");//,0,0,0);  
  //TODO set user limits

  G4VPhysicalVolume *targetPhysical = new G4PVPlacement(
                                      0,               // no rotation
                                      G4ThreeVector(), // at (0,0,0)
                                      targetLogical,   // its logical volume
                                      "target_P",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      0,               // copy number
                                      true);           // overlap checking

  return targetPhysical;
}

