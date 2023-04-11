
#include "DetectorSi.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>


#include <G4NistManager.hh>


DetectorSi::DetectorSi(G4LogicalVolume *parent) : fParent(parent) {

}

DetectorSi::~DetectorSi() { } 

G4VPhysicalVolume *DetectorSi::Construct() {
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* Si  = nist->FindOrBuildMaterial("G4_Si");

  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*CLHEP::g/CLHEP::mole;
  G4double density = 1.e-25*CLHEP::g/CLHEP::cm3;
  G4double temperature = 2.73*CLHEP::kelvin;
  G4double pressure = 3.e-18*CLHEP::pascal;
  G4Material* vacuum = new G4Material("interGalactic", atomicNumber,
                                       massOfMole, density, kStateGas,
                                       temperature, pressure);

  G4double cryst_dX = 0*CLHEP::cm;
  G4double cryst_dY = 2*CLHEP::cm;
  G4double cryst_dZ = 0.5*CLHEP::cm; 
  G4int nb_cryst = 8;
  G4double dPhi = CLHEP::twopi/nb_cryst, half_dPhi = 0.5*dPhi;
  G4double cosdPhi = std::cos(half_dPhi);
  G4double tandPhi = std::tan(half_dPhi);

  G4double ring_R1 = 8*CLHEP::cm;
  G4double ring_R2 = 9*CLHEP::cm;
  //G4double ring_R1 = 0.5*cryst_dY/tandPhi;
  //G4double ring_R2 = (ring_R1+cryst_dZ)/cosdPhi;

  G4Tubs* ring =
    new G4Tubs("Ring", ring_R1, ring_R2, 0.5*cryst_dY, 0., CLHEP::twopi);

  G4LogicalVolume* ringLogic =
    new G4LogicalVolume(ring,           //its solid
                        vacuum,                  //its material
                        "Ring");             //its name


  G4VSolid* detectorSi = new G4Tubs("detectorSi",cryst_dX,cryst_dY,cryst_dZ,
                                    0*CLHEP::deg,360.*CLHEP::deg);
  G4LogicalVolume* detectorSiLogic = new G4LogicalVolume(detectorSi, Si, "myDetectorSi");
/*
  G4VPhysicalVolume *detectorSiPhysical = new G4PVPlacement(
                                      0,               // no rotation
                                      G4ThreeVector(200,200,200), // at (0,0,0)
                                      detectorSiLogic,   // its logical volume
                                      "detectorSi_p",      // its name
                                      fParent,         // its morther volume (logical)
                                      false,           // no boolean operation
                                      0,               // copy number
                                      true);           // overlap checking
  G4cout << "PLACED DETECTOR" << G4endl;

  //

*/
  for (G4int icrys = 0; icrys < nb_cryst ; icrys++) {
    G4double phi = icrys*dPhi;
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateY(90*CLHEP::deg);
    rotm.rotateZ(phi);
    G4ThreeVector uz = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);
    G4ThreeVector position = (ring_R1+0.5*0.5*CLHEP::cm)*uz;
    G4Transform3D transform = G4Transform3D(rotm,position);

    G4VPhysicalVolume *detectorSiPhysical = new G4PVPlacement(
                      transform,             //rotation,position
                      detectorSiLogic,            //its logical volume
                      "detectorSi",             //its name
                      ringLogic,             //its mother  volume
                      false,                 //no boolean operation
                      icrys,                 //copy number
                      false);       // checking overlaps 


  }

  G4VPhysicalVolume *ringPhysical = new G4PVPlacement(
                    0,
                    G4ThreeVector(0,0,0),
                    ringLogic,
                    "ring",
                    fParent,
                    false,
                    0,
                    true);

  return ringPhysical;
}

