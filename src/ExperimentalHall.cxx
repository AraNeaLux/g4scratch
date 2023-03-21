
#include "ExperimentalHall.h"
#include "Materials.h"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>

#include <G4NistManager.hh>

ExperimentalHall::ExperimentalHall() {
  SetXYZ(200.*CLHEP::cm,200.*CLHEP::cm,200.*CLHEP::cm);


}

ExperimentalHall::~ExperimentalHall() { }

G4VPhysicalVolume *ExperimentalHall::Construct() {
  /* constrution order:
    - solid    - define object 
    - logical  - assign material
    - physical - assign placement and parent.
  */


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


  fExpHall         = new G4Box("expHallBox",fExpHallX,fExpHallY,fExpHallZ);
  //fExpHallLogical  = new G4LogicalVolume(fExpHall,Materials::Get("vac"),"exphall_L");  //0,0,0);
  fExpHallLogical  = new G4LogicalVolume(fExpHall,vacuum,"exphall_L");  //0,0,0);
  fExpHallPhysical = new G4PVPlacement(0,G4ThreeVector(),
                                       fExpHallLogical,"expHall",0,false,0,true);


  return fExpHallPhysical;
}

void ExperimentalHall::SetXYZ(double x,double y, double z) {
  fExpHallX = x;
  fExpHallY = y;
  fExpHallZ = z;

}




