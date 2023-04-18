
#include "VacChamber.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Sphere.hh>
#include <G4VisAttributes.hh>

#include <G4NistManager.hh>


VacChamber::VacChamber(G4LogicalVolume *parent) : fParent(parent) {

}

VacChamber::~VacChamber() { } 

G4VPhysicalVolume *VacChamber::Construct() {

  G4Sphere *vacChamber = new G4Sphere("vacChamber",14.*CLHEP::cm,16.*CLHEP::cm,0.*CLHEP::deg,360.*CLHEP::deg,0.*CLHEP::deg,170.*CLHEP::deg);
  G4LogicalVolume *vacChamberLogical = new G4LogicalVolume(vacChamber,Materials::Get("Al"),"vacChamber_L");//,0,0,0); 
  vacChamberLogical->SetVisAttributes(G4VisAttributes(false)); 
  //TODO set user limits

  G4VPhysicalVolume *vacChamberPhysical = new G4PVPlacement(
                                      0,               // no rotation
                                      G4ThreeVector(), // at (0,0,0)
                                      vacChamberLogical,   // its logical volume
                                      "vacChamber_P",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      0,               // copy number
                                      true);           // overlap checking

  return vacChamberPhysical;
}

