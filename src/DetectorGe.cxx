
#include "DetectorGe.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>


#include <G4NistManager.hh>

int DetectorGe::fCopyCounter = 100;

DetectorGe::DetectorGe(G4LogicalVolume *parent, double radius, double angle) : fParent(parent) {
  fRadius = radius;
  fAngle = angle;
  fCopyNum = fCopyCounter++;
  fCrystRad = 4.*CLHEP::cm;
  fCrystZ = 15.*CLHEP::cm/2.; // divide bc weird G4 things

}

DetectorGe::~DetectorGe() { } 

G4VPhysicalVolume *DetectorGe::Construct() {

  // Making a detector
  G4VSolid* detectorGe = new G4Tubs("detectorGe",0,fCrystRad,fCrystZ,
                                    0*CLHEP::deg,360.*CLHEP::deg);
  G4LogicalVolume* detectorGeLogic = new G4LogicalVolume(detectorGe, Materials::Get("Ge"), "detectorGe_l");

  // Place single detector

    G4double phi = fAngle*CLHEP::deg;
    G4RotationMatrix rotm;
    rotm.rotateY(phi);

    G4ThreeVector uz = G4ThreeVector(std::sin(phi),0.,  std::cos(phi));
    G4ThreeVector position = (fRadius*CLHEP::cm+fCrystZ/2.)*uz;
    G4Transform3D transform = G4Transform3D(rotm,position);

  G4VPhysicalVolume *detectorGePhysical = new G4PVPlacement(
                                      transform, 
                                      detectorGeLogic,   // its logical volume
                                      "detectorGe_p",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      fCopyNum,               // copy number
                                      true);           // overlap checking

  return detectorGePhysical;
}

