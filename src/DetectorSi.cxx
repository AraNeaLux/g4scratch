
#include "DetectorSi.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>


#include <G4NistManager.hh>

int DetectorSi::fCopyCounter = 100;

DetectorSi::DetectorSi(G4LogicalVolume *parent, double radius, double angle) : fParent(parent) {
  fRadius = radius;
  fAngle = angle;
  fCopyNum = fCopyCounter++;
  fCrystRad = 2*CLHEP::cm;
  fCrystZ = 0.5*CLHEP::cm;

}

DetectorSi::~DetectorSi() { } 

G4VPhysicalVolume *DetectorSi::Construct() {

  // Making a detector
  G4VSolid* detectorSi = new G4Tubs("detectorSi",0,fCrystRad,fCrystZ,
                                    0*CLHEP::deg,360.*CLHEP::deg);
  G4LogicalVolume* detectorSiLogic = new G4LogicalVolume(detectorSi, Materials::Get("Si"), "myDetectorSi");

  // Place single detector

    G4double phi = fAngle*CLHEP::deg;
    G4RotationMatrix rotm;
    rotm.rotateY(phi);

    G4ThreeVector uz = G4ThreeVector(std::sin(phi),0.,  std::cos(phi));
    G4ThreeVector position = (fRadius*CLHEP::cm)*uz;
    G4Transform3D transform = G4Transform3D(rotm,position);

  G4VPhysicalVolume *detectorSiPhysical = new G4PVPlacement(
                                      transform, 
                                      detectorSiLogic,   // its logical volume
                                      "detectorSi_p",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      fCopyNum,               // copy number
                                      true);           // overlap checking

  return detectorSiPhysical;
}

