

#include "MyDetectorConstruction.h"
//#include <filesystem>
#include <G4GDMLParser.hh>

void MyDetectorConstruction::WriteGDML(G4VPhysicalVolume *world) {
  G4GDMLParser parser;
  //std::filesystem::remove("geo_test.gdml");
  std::remove("geo_test.gdml");
  parser.Write("geo_test.gdml",world);
}


G4VPhysicalVolume* MyDetectorConstruction::Construct(){

  G4VSolid* solidWorld = new G4Box("World",
                                    10*cm,10*cm,10*cm);
  G4VSolid* solidTarget = new G4Box("Target",
                                    1*cm, 1*cm, 1*mm);
  G4VSolid* solidDetector = new G4Tubs("detector",
                                          0*cm,2*cm,0.5*cm,0*deg,360.*deg);
  

  // Pointer to Geant4's materials database
  G4NistManager* nist = G4NistManager::Instance();

  // Make Lead and Air materials from database
  G4Material* Ta  = nist->FindOrBuildMaterial("G4_Ta");
  G4Material* Si  = nist->FindOrBuildMaterial("G4_Si");
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 2.73*kelvin;
  G4double pressure = 3.e-18*pascal;
  G4Material* vacuum = new G4Material("interGalactic", atomicNumber,
                                       massOfMole, density, kStateGas,
                                       temperature, pressure);






  // Make the world air and the target lead
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, 
      vacuum, "myWorld");
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, 
      Ta, "myTarget");
  G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, 
      Si, "myDetector");





  // Place world
  //G4VPhysicalVolume* physWorld = new G4PVPlacement(
  fPhysWorld = new G4PVPlacement(
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


  // Set parameters for rotated placement
  G4int nb_cryst = 8;
  G4int ring_rad = 8*cm;
  G4double dPhi = CLHEP::twopi/nb_cryst, half_dPhi = 0.5*dPhi;
  G4double cosdPhi = std::cos(half_dPhi);
  G4double tandPhi = std::tan(half_dPhi);
  G4double ring_R1 = 0.5*ring_rad/tandPhi;

  // Place detector(s)
  for (G4int icrys = 0; icrys < nb_cryst ; icrys++) {
    G4double phi = icrys*dPhi;
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateY(90*CLHEP::deg);
    rotm.rotateZ(phi);
    G4ThreeVector uz = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);
    G4ThreeVector position = (ring_R1+0.5*0.5*cm)*uz;
    G4Transform3D transform = G4Transform3D(rotm,position);

    new G4PVPlacement(transform,             //rotation,position
                      logicDetector,            //its logical volume
                      "detector",             //its name
                      logicWorld,             //its mother  volume
                      false,                 //no boolean operation
                      icrys,                 //copy number
                      true);       // checking overlaps 
  }

/*
  // Place detector
  G4Transform3D t = G4Translate3D(0.,0.,7.*cm) * G4Rotate3D(1,G4ThreeVector(1,0,0).unit());
  G4Transform3D siplacement = G4Transform3D(G4RotationMatrix(0.,1.,.0), G4ThreeVector(0., 0., 7.*cm));
  G4VPhysicalVolume* physDetector = new G4PVPlacement(
      //siplacement,
      t,
      logicDetector,         //its logical volume
      "Detector",           //its name
      logicWorld,         //its mother  volume
      false,                      //no boolean operation
      0,                  //copy number
      true);                      //overlaps checking 


  // Place detector
  G4VPhysicalVolume* physDetector = new G4PVPlacement(
      new G4RotationMatrix(0,1,0),                  //no rotation
      G4ThreeVector(0,0,7*cm),    //at (0,0,0)
      logicDetector,         //its logical volume
      "Detector",           //its name
      logicWorld,         //its mother  volume
      false,                      //no boolean operation
      0,                  //copy number
      true);                      //overlaps checking 
*/




  WriteGDML(fPhysWorld);
  return fPhysWorld;

}


